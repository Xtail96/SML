#include "machine_tool.h"

MachineTool::MachineTool(QObject *parent) :
    QObject(parent),
    m_connections(QList<QMetaObject::Connection>()),
    m_repository(this),
    m_adapterServer(this),
    m_motionController(this),
    m_deviceController(this),
    m_adapterRegistrator(&m_motionController, &m_deviceController, this),
    m_adaptersLauncher(new AdaptersLauncher(this)),
    m_errors(this),
    m_executionQueue(QQueue<QByteArray>()),
    m_sendNextCommandMetaInfo(QMetaObject::Connection()),
    m_based(false)
{
    this->setupConnections();
    this->setErrorFlag(ERROR_CODE::DEVICE_ADAPTER_DISCONNECTED);
    this->setErrorFlag(ERROR_CODE::MOTION_ADAPTER_DISCONNECTED);

    SettingsManager s;
    quint16 port = quint16(s.get("ServerSettings", "ServerPort").toInt());
    m_adapterServer.open(port);
    this->launchAdapters();
}

MachineTool::~MachineTool()
{
    this->stopAdapters();
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

    m_connections.append(QObject::connect(&m_adapterServer, &AdapterGateway::newConnection, this, [=](QWebSocket* client) {
        m_adapterRegistrator.addClient(client);
    }));

    m_connections.append(QObject::connect(&m_motionController, &MotionController::connectionStateChanged, this, [=]() {
        m_motionController.isConnected()
                ? this->removeErrorFlag(ERROR_CODE::MOTION_ADAPTER_DISCONNECTED)
                : this->setErrorFlag(ERROR_CODE::MOTION_ADAPTER_DISCONNECTED);
    }));

    m_connections.append(QObject::connect(&m_deviceController, &DeviceController::connectionStateChanged, this, [=]() {
        m_deviceController.isConnected()
                ? this->removeErrorFlag(ERROR_CODE::DEVICE_ADAPTER_DISCONNECTED)
                : this->setErrorFlag(ERROR_CODE::DEVICE_ADAPTER_DISCONNECTED);
    }));

    /*
    m_connections.append(QObject::connect(&m_adapterServer, &SMLAdapterServer::errorOccurred, this, [=](ERROR_CODE errorCode) {
        this->setErrorFlag(errorCode);
    }));*/

    m_connections.append(QObject::connect(&m_errors, &SmlErrorFlags::stateChanged, this, [=]() {
        emit this->errorStateChanged(m_errors.getCurrentErrorFlags());
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

    /*for(auto sensor : m_repository.m_sensors)
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
        }));*/
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
        case ERROR_CODE::DEVICE_ADAPTER_DISCONNECTED:
            break;
        case ERROR_CODE::MOTION_ADAPTER_DISCONNECTED:
            this->setBased(false);
            break;
        case ERROR_CODE::UNKNOWN_ERROR:
            this->setBased(false);
            break;
        }
    }
}

void MachineTool::stopAdapters()
{
    try
    {
        m_adaptersLauncher.stopAdapters();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::stopAdapters: unknown error");
        this->setErrorFlag(UNKNOWN_ERROR);
    }
}

QStringList MachineTool::getConnectedAdapters()
{
    QStringList result = {};

    try
    {
        //result = m_adapterServer.currentAdapters();
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
    SettingsManager s;
    QString deviceAdapterPath = s.get("ExternalTools", "DeviceAdapter").toString();
    QString motionAdapterPath = s.get("ExternalTools", "MotionAdapter").toString();

    m_adaptersLauncher.startAdapters(deviceAdapterPath, motionAdapterPath);
}

bool MachineTool::isProgramEmpty()
{
    QStringList gcodes = m_repository.getGCodesProgram();
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

        //SwitchSpindelInteractor::execute(m_adapterServer, uid, true, rotations);
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

        //SwitchSpindelInteractor::execute(m_adapterServer, uid, false);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::switchSpindelOff: unknown error");
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
    }
}

bool MachineTool::isGCodesCorrect()
{
    try
    {
       QStringList gcodes = m_repository.getGCodesProgram();
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
                ? this->resumeProgramProcessing()
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

void MachineTool::pauseProgramProcessing()
{
    if(m_sendNextCommandMetaInfo)
        QObject::disconnect(m_sendNextCommandMetaInfo);
}

void MachineTool::resumeProgramProcessing()
{
    if(!m_sendNextCommandMetaInfo)
    {
        m_sendNextCommandMetaInfo = QObject::connect(this, &MachineTool::workflowStateChanged, this, [=](unsigned int deviceControllerWorkflowState, unsigned int motionControllerWorkflowState) {
            qDebug() << "MachineTool::resumeExecutionQueueProcessing:WorkflowStateChanged:" << deviceControllerWorkflowState << motionControllerWorkflowState;
            if((deviceControllerWorkflowState == 0) && (motionControllerWorkflowState == 0))
            {
                this->sendNextCommand();
            }
        });
    }

    this->sendNextCommand();
}

void MachineTool::stopProgramProcessing()
{
    // todo: terminate controller (may be kill adapter);
    this->pauseProgramProcessing();
    m_executionQueue.clear();
}

void MachineTool::stepMove(QMap<QString, double> steps)
{
    /*try
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
    }*/
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
        gcode += "F100";

        if(this->prepareExecutionQueue(QStringList {gcode}, false))
        {
            this->resumeProgramProcessing();
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
    /*try
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
    }*/
}

void MachineTool::resetCurrentCoordinates()
{
    /*try
    {
        Point zeroPoint = m_repository.createEmptyPoint();
        m_repository.setCurrentPosition(zeroPoint);
    }
    catch (...)
    {
        this->setErrorFlag(ERROR_CODE::SYNC_STATE_ERROR);
        qDebug() << "MachineTool::resetCurrentCoordinates: unknown error";
        this->setBased(false);
    }*/
}

void MachineTool::sendNextCommand()
{
    if(m_errors.isSystemHasErrors())
    {
        qDebug() << "MachineTool::sendNextCommand: error is occured during program processing.";
        this->stopProgramProcessing();
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        return;
    }

    if(m_executionQueue.isEmpty())
    {
        qDebug() << "MachineTool::sendNextCommand: queue is empty, program completed successfully";
        this->stopProgramProcessing();
        emit this->taskCompletedSuccesfully();
        return;
    }

    QByteArray cmd = m_executionQueue.dequeue();
    QString cmdStr = QString::fromUtf8(cmd);
    bool parsed = false;
    QtJson::JsonObject cmdObj = QtJson::parse(cmdStr, parsed).toMap();
    if(!parsed) { qDebug() << "MachineTool::sendNextCommand: analyse command error" << cmdStr; return; }

    if(!m_deviceController.isReady() || !m_motionController.isReady())
    {
        qDebug() << "MachineTool::sendNextCommand: duplicate send. DeviceControllerWorkflowSate ="
                 << m_deviceController.isReady()
                 << "MotionControllerWorkflowState =" << m_motionController.isReady();
        return;
    }

    QString target = cmdObj["target"].toString();
    if(target.toLower() == "devicecontroller")
    {
        qDebug() << "MachineTool::sendNextCommand:" << cmdStr;
        m_deviceController.sendMessage(cmd);
        emit this->commandSent(cmd);
        return;
    }

    if(target.toLower() == "motioncontroller")
    {
        qDebug() << "MachineTool::sendNextCommand:" << cmdStr;
        m_motionController.sendMessage(cmd);
        emit this->commandSent(cmd);
        return;
    }

    qDebug() << "MachineTool::sendNextCommand: unknown target" << target;
}
