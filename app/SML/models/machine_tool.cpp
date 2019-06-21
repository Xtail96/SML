#include "machine_tool.h"

MachineTool::MachineTool(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this)),
    m_adapterServer(new SMLServer(m_repository->m_port, this)),
    m_adaptersMonitor(new AdaptersMonitor(m_repository->m_u1Adapter.data(),
                                               m_repository->m_u2Adapter.data(),
                                               this)),
    m_pointsMonitor(new PointsMonitor(m_repository->m_pointsManager.data(), this)),
    m_sensorsMonitor(new SensorsMonitor(m_repository->m_sensors, this)),
    m_spindelsMonitor(new SpindelsMonitor(m_repository->m_spindels, this)),
    m_gcodesMonitor(new GCodesMonitor(m_repository->m_gcodesFilesManager.data(), this)),
    m_lastError(DISCONNECTED), // нет связи со станком
    m_executionQueue(QQueue<QByteArray>())
{
    this->setupConnections();
    this->startAdapterServer();
}

MachineTool::~MachineTool()
{
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
    QObject::connect(m_adapterServer.data(), SIGNAL(u2StateChanged(unsigned int, ERROR_CODE)),
                     this, SLOT(onAdapterServer_U2StateChanged(unsigned int, ERROR_CODE)));
    QObject::connect(m_adapterServer.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onAdapterServer_ErrorOccurred(ERROR_CODE)));

    QObject::connect(m_adaptersMonitor.data(), SIGNAL(AdapterConnectionStateChanged()), this, SLOT(onAdaptersMonitor_AdapterConnectionStateChanged()));
    QObject::connect(m_adaptersMonitor.data(), SIGNAL(AdapterWorkflowStateChanged()), this, SLOT(onAdaptersMonitor_AdapterWorkflowStateChanged()));

    QObject::connect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::connect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::connect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

    QObject::connect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::connect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QStringList)), this, SLOT(onGCodesMonitor_FileContentUpdated(QStringList)));
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
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u2StateChanged(unsigned int, ERROR_CODE)),
                     this, SLOT(onAdapterServer_U2StateChanged(unsigned int, ERROR_CODE)));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onAdapterServer_ErrorOccurred(ERROR_CODE)));

    QObject::disconnect(m_adaptersMonitor.data(), SIGNAL(AdapterConnectionStateChanged()), this, SLOT(onAdaptersMonitor_AdapterConnectionStateChanged()));
    QObject::disconnect(m_adaptersMonitor.data(), SIGNAL(AdapterWorkflowStateChanged()), this, SLOT(onAdaptersMonitor_AdapterWorkflowStateChanged()));

    QObject::disconnect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::disconnect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::disconnect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QStringList)), this, SLOT(onGCodesMonitor_FileContentUpdated(QStringList)));
}

ERROR_CODE MachineTool::checkMachineToolState()
{
    if(!this->checkAdapterConnections()) return ERROR_CODE::DISCONNECTED;

    return ERROR_CODE::OK;
}

bool MachineTool::checkAdapterConnections()
{
    return (m_repository->m_u1Adapter->connectionState() && m_repository->m_u2Adapter->connectionState());
}

void MachineTool::startAdapterServer()
{
    try
    {
        m_adapterServer->start();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::startAdapterServer: unknown error");
        this->setLastError(ROUTER_ERROR);
    }
}

void MachineTool::stopAdapterServer()
{
    try
    {
        m_adapterServer->stop();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::stopAdapterServer: unknown error");
        this->setLastError(ROUTER_ERROR);
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
        this->setLastError(ROUTER_ERROR);
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
        this->setLastError(ROUTER_ERROR);
    }

    return result;
}

ERROR_CODE MachineTool::getLastError()
{
    return m_lastError;
}

void MachineTool::setLastError(ERROR_CODE value)
{
    if(m_lastError == value)
    {
        emit this->errorStateChanged(m_lastError);
        return;
    }
    qDebug() << "MachineTool::setLastError: NEW_ERROR_CODE =" << value;

    switch (value)
    {
        case OK:
            break;
        case REPOSITORY_ERROR:
            /*
             * toDo: вызов интерактора (обработчика ошибки такого класса)
             */
            break;
        case DISCONNECTED:
            m_executionQueue.clear();
            break;
        default:
            break;
    }

    // вызов метода для проверки всех систем станка,
    // чтобы убедиться какой код ошибки нужно выставить в действительности
    qDebug() << "MachineTool::setLastError: checkMachineToolState started";
    m_lastError = this->checkMachineToolState();
    qDebug() << "MachineTool::setLastError: checkMachineToolState finished with ERROR_CODE =" << m_lastError;
    emit this->errorStateChanged(m_lastError);
}

void MachineTool::switchSpindelOn(QString uid, size_t rotations)
{
    try
    {
        if(m_lastError != OK)
        {
            return;
        }

        SwitchSpindelInteractor::execute(*(m_adapterServer.data()), uid, true, rotations);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::switchSpindelOn: unknown error");
        this->setLastError(ROUTER_ERROR);
    }
}

void MachineTool::switchSpindelOff(QString uid)
{
    try
    {
        if(m_lastError != OK)
        {
            return;
        }

        SwitchSpindelInteractor::execute(*(m_adapterServer.data()), uid, false);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::switchSpindelOff: unknown error");
        this->setLastError(ROUTER_ERROR);
    }
}

void MachineTool::executeProgram()
{
    if(m_lastError == ERROR_CODE::OK)
    {
        m_executionQueue.clear();
        try
        {
            m_executionQueue = PrepareExecutionQueueInteractor::execute(m_repository->getGCodesProgram());
        }
        catch(InvalidArgumentException e)
        {
            this->setLastError(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
            qDebug() << "MachineTool::executeProgram:" <<  e.what();
        }
        catch(...)
        {
            this->setLastError(ERROR_CODE::PROGRAM_EXECUTION_ERROR);
            qDebug() << "MachineTool::executeProgram: unknown error";
        }

        /*for(auto item : m_executionQueue)
        {
            qDebug() << QString::fromUtf8(item);
        }*/
        QObject::connect(this, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
        this->sendNextCommand();
    }
}

void MachineTool::onRepository_ErrorOccurred(ERROR_CODE code)
{
    this->setLastError(code);
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
    this->setLastError(lastError);
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

void MachineTool::onAdapterServer_U2StateChanged(unsigned int workflowState, ERROR_CODE lastError)
{
    //qDebug() << "MachineTool::onAdapterServer_U2StateChanged"
    //         << lastError << workflowState;
    this->setLastError(lastError);
    m_repository->setU2WorkflowState(workflowState);
}

void MachineTool::onAdapterServer_ErrorOccurred(ERROR_CODE errorCode)
{
    qDebug() << "MachineTool::onAdapterServer_ErrorOccurred" << errorCode;
    this->setLastError(errorCode);
}

void MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged()
{
    try
    {
        bool u1 = m_repository->m_u1Adapter->connectionState();
        bool u2 = m_repository->m_u2Adapter->connectionState();

        if(u1 && u2)
        {
            qDebug() << "MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: CONNECTED";
            this->setLastError(OK);
        }
        else
        {
            qDebug() << "MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: DISCONNECTED";
            this->setLastError(DISCONNECTED);
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged: unknown error");
        this->setLastError(ROUTER_ERROR);
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
        this->setLastError(ROUTER_ERROR);
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

void MachineTool::sendNextCommand()
{
    if(m_executionQueue.isEmpty())
    {
        qDebug() << "MachineTool::sendNextCommand: queue is empty, program completed successfully";
        QObject::disconnect(this, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
        emit this->programCompletedSuccesfully();
        return;
    }

    QByteArray message = m_executionQueue.dequeue();
    qDebug() << "MachineTool::sendNextCommand:" << QString::fromUtf8(message);
    m_adapterServer->sendMessage(message);
}

void MachineTool::onMachineTool_WorkflowStateChanged(unsigned int u1State, unsigned int u2State)
{
    //qDebug() << "MachineTool::onMachineTool_WorkflowStateChanged:" << u1State << u2State;
    if((u1State == 0) && (u2State == 0))
    {
        this->sendNextCommand();
    }
}
