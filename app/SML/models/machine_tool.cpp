#include "machine_tool.h"

MachineTool::MachineTool(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this)),
    m_adapterServer(new SMLAdapterServer(m_repository->m_port, this)),
    m_errors(new SmlErrorFlags(this)),
    m_errorFlagsMonitor(new ErrorFlagsMonitor(m_errors.data(), this)),
    m_adaptersMonitor(new AdaptersMonitor(m_repository->m_u1Adapter.data(),
                                               m_repository->m_u2Adapter.data(),
                                               this)),
    m_pointsMonitor(new PointsMonitor(m_repository->m_pointsManager.data(), this)),
    m_sensorsMonitor(new SensorsMonitor(m_repository->m_sensors, this)),
    m_spindelsMonitor(new SpindelsMonitor(m_repository->m_spindels, this)),
    m_gcodesMonitor(new GCodesMonitor(m_repository->m_gcodesFilesManager.data(), this)),
    m_axisesMonitor(new AxisesMonitor(m_repository->m_axises, this)),
    m_executionQueue(QQueue<QByteArray>()),
    m_based(false),
    m_adaptersLauncher(new AdaptersLauncher(this))
{
    this->setupConnections();
    this->startAdapterServer();
    this->setErrorFlag(ERROR_CODE::U1_DISCONNECTED);
    this->setErrorFlag(ERROR_CODE::U2_DISCONNECTED);
    //this->setBased(false);
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
    return *m_repository.data();
}

void MachineTool::setupConnections()
{
    QObject::connect(m_repository.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onRepository_ErrorOccurred(ERROR_CODE)));

    QObject::connect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onAdapterServer_U1Connected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onAdapterServer_U1Disconnected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)),
                     this, SLOT(onAdapterServer_U1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)));
    QObject::connect(m_adapterServer.data(), SIGNAL(u2Connected()), this, SLOT(onAdapterServer_U2Connected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u2Disconnected()), this, SLOT(onAdapterServer_U2Disconnected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u2StateChanged(QMap<QString, double>,unsigned int, ERROR_CODE)),
                     this, SLOT(onAdapterServer_U2StateChanged(QMap<QString, double>,unsigned int, ERROR_CODE)));
    QObject::connect(m_adapterServer.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onAdapterServer_ErrorOccurred(ERROR_CODE)));

    QObject::connect(m_errorFlagsMonitor.data(), SIGNAL(errorFlagsStateChanged()), this, SLOT(onErrorFlagsMonitor_ErrorFlagsStateChanged()));

    QObject::connect(m_adaptersMonitor.data(), SIGNAL(adapterConnectionStateChanged()), this, SLOT(onAdaptersMonitor_AdapterConnectionStateChanged()));
    QObject::connect(m_adaptersMonitor.data(), SIGNAL(adapterWorkflowStateChanged()), this, SLOT(onAdaptersMonitor_AdapterWorkflowStateChanged()));

    QObject::connect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::connect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::connect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

    QObject::connect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::connect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QStringList)), this, SLOT(onGCodesMonitor_FileContentUpdated(QStringList)));

    QObject::connect(m_axisesMonitor.data(), SIGNAL(axisCurrentPositionChanged(QString, double)), this, SLOT(onAxisesMonitor_AxisCurrentPositionChanged(QString, double)));
}

void MachineTool::resetConnections()
{  
    QObject::disconnect(m_repository.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onRepository_ErrorOccurred(ERROR_CODE)));

    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onAdapterServer_U1Connected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onAdapterServer_U1Disconnected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)),
                     this, SLOT(onAdapterServer_U1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u2Connected()), this, SLOT(onAdapterServer_U2Connected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u2Disconnected()), this, SLOT(onAdapterServer_U2Disconnected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u2StateChanged(QMap<QString, double>,unsigned int, ERROR_CODE)),
                     this, SLOT(onAdapterServer_U2StateChanged(QMap<QString, double>,unsigned int, ERROR_CODE)));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onAdapterServer_ErrorOccurred(ERROR_CODE)));

    QObject::disconnect(m_errorFlagsMonitor.data(), SIGNAL(errorFlagsStateChanged()), this, SLOT(onErrorFlagsMonitor_ErrorFlagsStateChanged()));

    QObject::disconnect(m_adaptersMonitor.data(), SIGNAL(adapterConnectionStateChanged()), this, SLOT(onAdaptersMonitor_AdapterConnectionStateChanged()));
    QObject::disconnect(m_adaptersMonitor.data(), SIGNAL(adapterWorkflowStateChanged()), this, SLOT(onAdaptersMonitor_AdapterWorkflowStateChanged()));

    QObject::disconnect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::disconnect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::disconnect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QStringList)), this, SLOT(onGCodesMonitor_FileContentUpdated(QStringList)));

    QObject::connect(m_axisesMonitor.data(), SIGNAL(axisCurrentPositionChanged(QString, double)), this, SLOT(onAxisesMonitor_AxisCurrentPositionChanged(QString, double)));
}

void MachineTool::handleErrors()
{
    QList<ERROR_CODE> currentErrors = m_errors->getCurrentErrorFlags();
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
        m_adapterServer->start();
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
        m_adapterServer->stop();
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
        result = m_adapterServer->currentAdapters();
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
        result = QString::number(m_adapterServer->port());
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
    return m_errors->getCurrentErrorFlags();
}

void MachineTool::setErrorFlag(ERROR_CODE code)
{
    if(code == ERROR_CODE::OK) return;

    qDebug() << "MachineTool::setErrorFlag: ERROR_CODE =" << code;
    m_errors->insertErrorFlag(code);
    this->handleErrors();
}

void MachineTool::removeErrorFlag(ERROR_CODE code)
{
    qDebug() << "MachineTool::removeErrorFlag: ERROR_CODE =" << code;
    m_errors->dropErrorFlag(code);
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
    m_adaptersLauncher->startAdapters(m_repository->m_u1Adapter->path(), m_repository->m_u2Adapter->path());
}

void MachineTool::stopAdapters()
{
    m_adaptersLauncher->stopAdapters();
}

void MachineTool::switchSpindelOn(QString uid, size_t rotations)
{
    try
    {
        if(m_errors->isSystemHasErrors())
        {
            return;
        }

        SwitchSpindelInteractor::execute(*(m_adapterServer.data()), uid, true, rotations);
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
        if(m_errors->isSystemHasErrors())
        {
            return;
        }

        SwitchSpindelInteractor::execute(*(m_adapterServer.data()), uid, false);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::switchSpindelOff: unknown error");
        this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
    }
}

void MachineTool::startProgramProcessing()
{
    try
    {
        if(this->prepareExecutionQueue(m_repository->getGCodesProgram()))
        {
            this->resumeExecutionQueueProcessing();
        }
        else
        {
            QMessageBox(QMessageBox::Warning, "Ошибка подготовки УП", "Произошла ошибка при подготовке УП к исполнению.").exec();
            this->setErrorFlag(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
        }
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

bool MachineTool::prepareExecutionQueue(QStringList gcodes)
{
    try
    {
        m_executionQueue.clear();
        if(!m_errors->isSystemHasErrors())
        {
            m_executionQueue = PrepareExecutionQueueInteractor::execute(gcodes);
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
    // kill adapter and terminate controller;
}

void MachineTool::moveToPoint(Point pointFromBase)
{
    try
    {
        QString gcode = "G1 ";
        for(size_t i = 0; i < pointFromBase.size(); i++)
        {
            gcode += SML_AXISES_NAMES.getNameByKey(i) + QString::number(pointFromBase.get(i)) + " ";
        }
        gcode += "F" + QString::number(m_repository->getVelocity());

        if(this->prepareExecutionQueue(QStringList {gcode}))
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
        m_repository->setCurrentCoordinates(m_repository->getMaxPosition());

        QStringList axisesNames = m_repository->getAxisesNames();
        QStringList sensorUids = {};
        for(auto name : axisesNames)
        {
            sensorUids.append("SensorAxis" + name);
        }

        for(auto uid : sensorUids)
        {
            if(m_repository->sensorExists(uid))
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
        Point zeroPoint = Point(m_repository->getAxisesCount());
        m_repository->setCurrentCoordinates(zeroPoint);
    }
    catch (...)
    {
        this->setErrorFlag(ERROR_CODE::SYNC_STATE_ERROR);
        qDebug() << "MachineTool::resetCurrentCoordinates: unknown error";
        this->setBased(false);
    }
}

void MachineTool::onRepository_ErrorOccurred(ERROR_CODE flag)
{
    this->setErrorFlag(flag);
}

void MachineTool::onErrorFlagsMonitor_ErrorFlagsStateChanged()
{
    emit this->errorStateChanged(m_errors->getCurrentErrorFlags());
}

void MachineTool::onAdapterServer_U1Connected()
{
    qDebug() << "MachineTool::onAdapterServer_U1Connected";
    m_repository->setU1ConnectState(true);
}

void MachineTool::onAdapterServer_U1Disconnected()
{
    qDebug() << "MachineTool::onAdapterServer_U1Disconnected";
    m_repository->setU1ConnectState(false);
}

void MachineTool::onAdapterServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, unsigned int workflowState, ERROR_CODE lastError)
{
    //qDebug() << "MachineTool::onAdapterServer_U1StateChanged"
    //         << lastError << sensors << devices << workflowState;
    this->setErrorFlag(lastError);
    m_repository->setU1Sensors(sensors);
    m_repository->setU1Devices(devices);
    m_repository->setU1WorkflowState(workflowState);
}

void MachineTool::onAdapterServer_U2Connected()
{
    qDebug() << "MachineTool::onAdapterServer_U2Connected";
    m_repository->setU2ConnectState(true);
}

void MachineTool::onAdapterServer_U2Disconnected()
{
    qDebug() << "MachineTool::onAdapterServer_U2Disconnected";
    m_repository->setU2ConnectState(false);
}

void MachineTool::onAdapterServer_U2StateChanged(QMap<QString, double> coordinates, unsigned int workflowState, ERROR_CODE lastError)
{
    this->setErrorFlag(lastError);
    m_repository->setU2WorkflowState(workflowState);
    m_repository->setCurrentCoordinates(coordinates);
}

void MachineTool::onAdapterServer_ErrorOccurred(ERROR_CODE errorCode)
{
    qDebug() << "MachineTool::onAdapterServer_ErrorOccurred" << errorCode;
    this->setErrorFlag(errorCode);
}

void MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged()
{
    try
    {
        bool u1 = m_repository->m_u1Adapter->connectionState();
        bool u2 = m_repository->m_u2Adapter->connectionState();

        if(u1)
        {
            qDebug() << "MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: U1_DISCONNECTED = false";
            this->removeErrorFlag(ERROR_CODE::U1_DISCONNECTED);
        }
        else
        {
            qDebug() << "MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: U1_DISCONNECTED = true";
            this->setErrorFlag(ERROR_CODE::U1_DISCONNECTED);
        }

        if(u2)
        {
            qDebug() << "MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: U2_DISCONNECTED = false";
            this->removeErrorFlag(ERROR_CODE::U2_DISCONNECTED);
        }
        else
        {
            qDebug() << "MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: U2_DISCONNECTED = true";
            this->setErrorFlag(ERROR_CODE::U2_DISCONNECTED);
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: unknown error");
        this->setErrorFlag(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void MachineTool::onAdaptersMonitor_AdapterWorkflowStateChanged()
{
    emit this->workflowStateChanged(m_repository->m_u1Adapter->workflowState(), m_repository->m_u2Adapter->workflowState());
}

void MachineTool::onPointsMonitor_PointsUpdated()
{
    emit this->pointsUpdated();
}

void MachineTool::onSensorMonitor_StateChanged(QString sensorUid, bool state)
{
    try
    {
        /*if(sensorName == "name")
        {
            do somtething
        }*/
        emit this->sensorStateChanged(sensorUid, state);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::onSensorMonitor_StateChanged: unknown error");
        this->setErrorFlag(UNKNOWN_ERROR);
    }
}

void MachineTool::onSpindelsMonitor_StateChanged(QString index, bool state, size_t rotations)
{
    emit this->spindelStateChanged(index, state, rotations);
}

void MachineTool::onGCodesMonitor_FilePathUpdated(QString path)
{
    emit this->gcodesFilePathUpdated(path);
}

void MachineTool::onGCodesMonitor_FileContentUpdated(QStringList content)
{
    emit this->gcodesFileContentUpdated(content);
}

void MachineTool::onAxisesMonitor_AxisCurrentPositionChanged(QString, double)
{
    emit this->currentCoordinatesChanged();
}

void MachineTool::sendNextCommand()
{
    if(m_errors->isSystemHasErrors())
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

    QByteArray message = m_executionQueue.dequeue();
    qDebug() << "MachineTool::sendNextCommand:" << QString::fromUtf8(message);
    m_adapterServer->sendMessage(message);
    emit this->nextCommandSent(message);
}

void MachineTool::onMachineTool_WorkflowStateChanged(unsigned int u1WorkflowState, unsigned int u2WorkflowState)
{
    //qDebug() << "MachineTool::onMachineTool_WorkflowStateChanged:" << u1State << u2State;
    if((u1WorkflowState == 0) && (u2WorkflowState == 0))
    {
        this->sendNextCommand();
    }
}
