#include "machine_tool.h"

MachineTool::MachineTool(QObject *parent) : QObject(parent),
    m_connections(QList<QMetaObject::Connection>()),
    m_repository(this),
    m_adapterServer(m_repository.m_port, this),
    m_errors(this),
    m_executionQueue(QQueue<QByteArray>()),
    m_based(false),
    m_adaptersLauncher(new AdaptersLauncher(this))
{
    this->setupConnections();
    this->startAdapterServer();
    this->setErrorFlag(ERROR_CODE::U1_DISCONNECTED);
    this->setErrorFlag(ERROR_CODE::U2_DISCONNECTED);
}

MachineTool::~MachineTool()
{
    this->stopAdapterServer();
    this->resetConnections();
}

MachineTool &MachineTool::getInstance()
{
    static QScopedPointer<MachineTool> m_instance;
    if(m_instance.data() == nullptr)
    {
        m_instance.reset( new MachineTool() );
    }
    return *m_instance;
}

Repository &MachineTool::getRepository()
{
    return m_repository;
}

void MachineTool::setupConnections()
{
    this->resetConnections();

    m_connections.append(QObject::connect(&m_repository, &Repository::errorOccurred, this, [=](ERROR_CODE flag) {
        this->setErrorFlag(flag);
    }));

    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::u1Connected, this, [=]() {
        qDebug() << "U1Connected";
        m_repository.setU1ConnectState(true);
        GetAdapterCurrentStateInteractor::execute(m_adapterServer, Adapter::U1);
    }));

    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::u1Disconnected, this, [=]() {
        qDebug() << "U1Disconnected";
        m_repository.setU1ConnectState(false);
    }));

    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::u1StateChanged, this, [=](QList<QVariant> sensors, QList<QVariant> devices, unsigned int workflowState, ERROR_CODE lastError) {
        this->setErrorFlag(lastError);
        m_repository.setU1Sensors(sensors);
        m_repository.setU1Devices(devices);
        m_repository.setU1WorkflowState(workflowState);
    }));

    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::u2Connected, this, [=]() {
        qDebug() << "U2Connected";
        m_repository.setU2ConnectState(true);
        GetAdapterCurrentStateInteractor::execute(m_adapterServer, Adapter::U2);
    }));

    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::u2Disconnected, this, [=]() {
        qDebug() << "U2Disconnected";
        m_repository.setU2ConnectState(false);
    }));

    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::u2StateChanged, this, [=](QMap<QString, double> coordinates, unsigned int workflowState, ERROR_CODE lastError) {
        this->setErrorFlag(lastError);
        m_repository.setU2WorkflowState(workflowState);
        m_repository.setCurrentPosition(coordinates);
    }));

    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::errorOccurred, this, [=](ERROR_CODE errorCode) {
        this->setErrorFlag(errorCode);
    }));

    m_connections.append(QObject::connect(&m_errors, &SmlErrorFlags::stateChanged, this, [=]() {
        emit this->errorStateChanged(m_errors.getCurrentErrorFlags());
    }));

    m_connections.append(QObject::connect(&m_repository.m_u1Adapter, &Adapter::connectionStateChanged, this, [=]() {
        m_repository.m_u1Adapter.connectionState()
                ? this->removeErrorFlag(ERROR_CODE::U1_DISCONNECTED)
                : this->setErrorFlag(ERROR_CODE::U1_DISCONNECTED);
    }));

    m_connections.append(QObject::connect(&m_repository.m_u2Adapter, &Adapter::connectionStateChanged, this, [=]() {
        m_repository.m_u2Adapter.connectionState()
                ? this->removeErrorFlag(ERROR_CODE::U2_DISCONNECTED)
                : this->setErrorFlag(ERROR_CODE::U2_DISCONNECTED);
    }));

    m_connections.append(QObject::connect(&m_repository.m_u1Adapter, &Adapter::workflowStateChanged, this, [=]() {
        emit this->workflowStateChanged(m_repository.m_u1Adapter.workflowState(), m_repository.m_u2Adapter.workflowState());
    }));

    m_connections.append(QObject::connect(&m_repository.m_u2Adapter, &Adapter::workflowStateChanged, this, [=]() {
        emit this->workflowStateChanged(m_repository.m_u1Adapter.workflowState(), m_repository.m_u2Adapter.workflowState());
    }));

    m_connections.append(QObject::connect(&m_repository, &Repository::pointsUpdated, this, [=]() {
        emit this->pointsUpdated();
    }));

    m_connections.append(QObject::connect(&m_repository.m_gcodesFilesManager, &GCodesFileManager::filePathUpdated, this, [=]() {
        emit this->gcodesFilePathUpdated(m_repository.m_gcodesFilesManager.getFilePath());
    }));

    m_connections.append(QObject::connect(&m_repository.m_gcodesFilesManager, &GCodesFileManager::fileContentUpdated, this, [=]() {
        emit this->gcodesFileContentUpdated(m_repository.m_gcodesFilesManager.getContent());
    }));

    for(auto sensor : m_repository.m_sensors)
        m_connections.append(QObject::connect(sensor.data(), &Sensor::stateChanged, this, [=]() {
            emit this->sensorStateChanged(sensor.data()->uid(), sensor.data()->isEnable());
        }));

    for(auto spindel : m_repository.m_spindels)
        m_connections.append(QObject::connect(spindel.data(), &Spindel::stateChanged, this, [=]() {
            emit this->spindelStateChanged(spindel.data()->getUid(),
                                           spindel.data()->isEnable(),
                                           spindel.data()->getCurrentRotations());
        }));

    for(auto axis : m_repository.m_axes)
        m_connections.append(QObject::connect(axis.data(), &Axis::currentPositionChanged, this, [=]() {
            emit this->currentCoordinatesChanged();
        }));
}

void MachineTool::resetConnections()
{
    for(auto& connection : m_connections)
    {
        QObject::disconnect(connection);
    }
}

void MachineTool::handleErrors()
{
    QList<ERROR_CODE> currentErrors = m_errors.getCurrentErrorFlags();
    for(ERROR_CODE error : currentErrors)
    {
        switch (error)
        {
        case ERROR_CODE::OK:
            break;
        case ERROR_CODE::INVALID_SETTINGS:
            break;
        case ERROR_CODE::PROGRAM_EXECUTION_ERROR:
            m_executionQueue.clear();
            emit this->taskCompletedWithErrors();
            this->removeErrorFlag(error);
            break;
        case ERROR_CODE::SYNC_STATE_ERROR:
            this->setBased(false);
            break;
        case ERROR_CODE::U1_DISCONNECTED:
            break;
        case ERROR_CODE::U2_DISCONNECTED:
            this->setBased(false);
            break;
        case ERROR_CODE::UNKNOWN_ERROR:
            this->setBased(false);
            break;
        }
    }
}

void MachineTool::startAdapterServer()
{
    try
    {
        m_adapterServer.start();
        this->launchAdapters();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::startAdapterServer: unknown error");
        this->setErrorFlag(UNKNOWN_ERROR);
    }
}

void MachineTool::stopAdapterServer()
{
    try
    {
        m_adapterServer.stop();
        this->stopAdapters();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::stopAdapterServer: unknown error");
        this->setErrorFlag(UNKNOWN_ERROR);
    }
}

QStringList MachineTool::getConnectedAdapters()
{
    QStringList result = {};

    try
    {
        result = m_adapterServer.currentAdapters();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::getConnectedAdapters: unknown error");
        this->setErrorFlag(UNKNOWN_ERROR);
    }

    return result;
}

QString MachineTool::getAdapterServerPort()
{
    QString result = QString();

    try
    {
        result = QString::number(m_adapterServer.port());
    }
    catch (...)
    {
        qDebug() << QStringLiteral("MachineTool::getAdapterServerPort: unknown error");
        this->setErrorFlag(UNKNOWN_ERROR);
    }

    return result;
}

QList<ERROR_CODE> MachineTool::getCurrentErrorFlags()
{
    return m_errors.getCurrentErrorFlags();
}

void MachineTool::setErrorFlag(ERROR_CODE code)
{
    if(code == ERROR_CODE::OK) return;

    qDebug() << "MachineTool::setErrorFlag: ERROR_CODE =" << code;
    m_errors.insertErrorFlag(code);
    this->handleErrors();
}

void MachineTool::removeErrorFlag(ERROR_CODE code)
{
    qDebug() << "MachineTool::removeErrorFlag: ERROR_CODE =" << code;
    m_errors.dropErrorFlag(code);
}

bool MachineTool::getBased() const
{
    return m_based;
}

void MachineTool::setBased(bool based)
{
    m_based = based;
    emit this->basingStateChanged(m_based);
}

void MachineTool::launchAdapters()
{
    m_adaptersLauncher.startAdapters(m_repository.m_u1Adapter.path(), m_repository.m_u2Adapter.path());
}

void MachineTool::stopAdapters()
{
    m_adaptersLauncher.stopAdapters();
}

bool MachineTool::isProgramEmpty(QStringList gcodes)
{
    if(gcodes.length() <= 0) return true;

    if(gcodes.join("") == "") return true;

    QString token = gcodes.join("");
    token = token.remove("\n");
    token = token.remove("\r");
    token = token.remove("\t");
    token = token.remove(" ");
    if(token.length() <= 0 || token == "") return true;

    return false;
}

void MachineTool::switchSpindelOn(QString uid, size_t rotations)
{
    try
    {
        if(m_errors.isSystemHasErrors()) return;

        SwitchSpindelInteractor::execute(m_adapterServer, uid, true, rotations);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::switchSpindelOn: unknown error");
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
    }
}

void MachineTool::switchSpindelOff(QString uid)
{
    try
    {
        if(m_errors.isSystemHasErrors()) return;

        SwitchSpindelInteractor::execute(m_adapterServer, uid, false);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::switchSpindelOff: unknown error");
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
    }
}

bool MachineTool::isGCodesCorrect(QStringList gcodes)
{
    try
    {
       QQueue<QByteArray> result = PrepareExecutionQueueInteractor::execute(gcodes, true);
       if(result.length() <= 0) return false;
       result.clear();

       result = PrepareExecutionQueueInteractor::execute(gcodes, false);
       return result.length() > 0;
    }
    catch(...)
    {
        qDebug() << "MachineTool::isGCodesCorrect: unknown error";
        return false;
    }
}

void MachineTool::startProgramProcessing()
{
    try
    {
        this->prepareExecutionQueue(m_repository.getGCodesProgram(), true)
                ? this->resumeExecutionQueueProcessing()
                : this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
    }
    catch(InvalidArgumentException e)
    {
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        qDebug() << "MachineTool::startProgramProcessing:" <<  e.what();
    }
    catch(...)
    {
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        qDebug() << "MachineTool::startProgramProcessing: unknown error";
    }
}

bool MachineTool::prepareExecutionQueue(QStringList gcodes, bool resolveToCurrentPosition)
{
    try
    {
        m_executionQueue.clear();
        if(!m_errors.isSystemHasErrors())
        {
            m_executionQueue = PrepareExecutionQueueInteractor::execute(gcodes, resolveToCurrentPosition);
            return true;
        }
        else
        {
            return false;
        }
    }
    catch(...)
    {
        qDebug() << "MachineTool::prepareExecutionQueue: unknown error";
        m_executionQueue.clear();
        return false;
    }
}

void MachineTool::pauseExecutionQueueProcessing()
{
    QObject::disconnect(this, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
}

void MachineTool::resumeExecutionQueueProcessing()
{
    QObject::connect(this, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
    this->sendNextCommand();
}

void MachineTool::stopExecutionQueueProcessing()
{
    // todo: terminate controller (may be kill adapter);
    QObject::disconnect(this, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
    m_executionQueue.clear();
}

void MachineTool::stepMove(QMap<QString, double> steps)
{
    try
    {
        Point currentCoordinatesFromBase = m_repository.getCurrentPositionFromBase();
        Point increment = m_repository.createEmptyPoint();

        QStringList axises = steps.keys();
        for(auto axis : axises)
        {
            increment.insertAxis(axis, steps[axis]);
        }

        Point target = currentCoordinatesFromBase + increment;
        this->moveToPoint(target);
    }
    catch(InvalidArgumentException e)
    {
        QMessageBox(QMessageBox::Critical, "Ошибка", e.what()).exec();
    }
}

void MachineTool::moveToPoint(Point pointFromBase)
{
    try
    {
        QString gcode = "G1 ";
        QMap<QString, double> coords = pointFromBase.coordsMap();
        for(QString axisUid : coords.keys())
        {
            gcode += axisUid + QString::number(coords[axisUid]);
        }
        gcode += "F" + QString::number(m_repository.getVelocity());

        if(this->prepareExecutionQueue(QStringList {gcode}, false))
        {
            this->resumeExecutionQueueProcessing();
        }
        else
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", "Ошибка подготовки g-кода для перемещения").exec();
        }
    }
    catch(InvalidArgumentException e)
    {
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        qDebug() << "MachineTool::moveToPoint:" <<  e.what();
    }
    catch(...)
    {
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        qDebug() << "MachineTool::moveToPoint: unknown error";
    }
}

void MachineTool::moveToSensor(QString sensorUid)
{
    qDebug() << "MachineTool::moveToSensor(" + sensorUid + ")";
}

void MachineTool::moveToBase()
{
    try
    {
        this->setBased(false);
        m_repository.setCurrentPosition(m_repository.getMaxPosition());

        QStringList axisesNames = m_repository.getAxisesNames();
        QStringList sensorUids = {};
        for(auto name : axisesNames)
        {
            sensorUids.append("SensorAxis" + name);
        }

        for(auto uid : sensorUids)
        {
            if(m_repository.sensorExists(uid))
            {
                this->moveToSensor(uid);
            }
        }

        this->resetCurrentCoordinates();
        this->setBased(true);
    }
    catch(InvalidArgumentException e)
    {
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        qDebug() << "MachineTool::moveToBase:" <<  e.what();
        this->setBased(false);
    }
    catch (...)
    {
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        qDebug() << "MachineTool::moveToBase: unknown error";
        this->setBased(false);
    }
}

void MachineTool::resetCurrentCoordinates()
{
    try
    {
        Point zeroPoint = m_repository.createEmptyPoint();
        m_repository.setCurrentPosition(zeroPoint);
    }
    catch (...)
    {
        this->setErrorFlag(ERROR_CODE::SYNC_STATE_ERROR);
        qDebug() << "MachineTool::resetCurrentCoordinates: unknown error";
        this->setBased(false);
    }
}

void MachineTool::sendNextCommand()
{
    if(m_errors.isSystemHasErrors())
    {
        qDebug() << "MachineTool::sendNextCommand: error is occured during program processing.";
        QObject::disconnect(this, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        return;
    }

    if(m_executionQueue.isEmpty())
    {
        qDebug() << "MachineTool::sendNextCommand: queue is empty, program completed successfully";
        QObject::disconnect(this, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
        emit this->taskCompletedSuccesfully();
        return;
    }

    if((m_repository.m_u1Adapter.workflowState() != 0) || (m_repository.m_u1Adapter.workflowState() != 0))
    {
        qDebug() << "MachineTool::sendNextCommand: duplicate send. U1WorkflowSate =" << m_repository.m_u1Adapter.workflowState() << "U2WorkflowState =" << m_repository.m_u2Adapter.workflowState();
        return;
    }

    QByteArray cmd = m_executionQueue.dequeue();
    QString cmdStr = QString::fromUtf8(cmd);
    bool parsed = false;
    QtJson::JsonObject cmdObj = QtJson::parse(cmdStr, parsed).toMap();
    if(!parsed) { qDebug() << "MachineTool::sendNextCommand: analyse command error" << cmdStr; return; }

    QString target = cmdObj["target"].toString();
    if(target.toLower() == "u1")
    {
        qDebug() << "MachineTool::sendNextCommand:" << cmdStr;
        m_adapterServer.sendMessageToU1(cmd);
        emit this->nextCommandSent(cmd);

        m_repository.m_u1Adapter.setWorkflowState(1);
        return;
    }

    if(target.toLower() == "u2")
    {
        qDebug() << "MachineTool::sendNextCommand:" << cmdStr;
        m_adapterServer.sendMessageToU2(cmd);
        emit this->nextCommandSent(cmd);

        m_repository.m_u2Adapter.setWorkflowState(1);
        return;
    }

    qDebug() << "MachineTool::sendNextCommand: unknown target" << target;
}

void MachineTool::onMachineTool_WorkflowStateChanged(unsigned int u1WorkflowState, unsigned int u2WorkflowState)
{
    qDebug() << "MachineTool::onMachineTool_WorkflowStateChanged:" << u1WorkflowState << u2WorkflowState;
    if((u1WorkflowState == 0) && (u2WorkflowState == 0))
    {
        this->sendNextCommand();
    }
}
