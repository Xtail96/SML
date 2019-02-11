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
    m_lastError(DISCONNECTED) // нет связи со станком
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

Repository *MachineTool::getRepository()
{
    return m_repository.data();
}

void MachineTool::setupConnections()
{
    QObject::connect(m_repository.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onRepository_ErrorOccurred(ERROR_CODE)));

    QObject::connect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)));
    QObject::connect(m_adapterServer.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onServer_ErrorOccurred(ERROR_CODE)));

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

    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, ERROR_CODE)));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(errorOccurred(ERROR_CODE)), this, SLOT(onServer_ErrorOccurred(ERROR_CODE)));

    QObject::disconnect(m_adaptersMonitor.data(), SIGNAL(AdapterConnectionStateChanged()), this, SLOT(onAdaptersMonitor_AdapterConnectionStateChanged()));
    QObject::disconnect(m_adaptersMonitor.data(), SIGNAL(AdapterWorkflowStateChanged()), this, SLOT(onAdaptersMonitor_AdapterWorkflowStateChanged()));

    QObject::disconnect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::disconnect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::disconnect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QStringList)), this, SLOT(onGCodesMonitor_FileContentUpdated(QStringList)));
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
    m_lastError = value;

    switch (value)
    {
        case OK:
            /*
             * toDo: вызов метода для проверки всех систем,
             * чтобы убедиться, что все действительно ОК
             */
            break;
        case REPOSITORY_ERROR:
            /*
             * toDo: вызов интерактора (обработчика ошибки такого класса)
             */
            break;
        default:
            break;
    }

    emit this->errorOccurred(m_lastError);
}

void MachineTool::switchSpindelOn(QString uid, size_t rotations)
{
    try
    {
        if(m_lastError != OK)
        {
            return;
        }

        SwitchSpindel swithcer(m_adapterServer.data(), uid, true, rotations);
        swithcer.execute();
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

        SwitchSpindel switcher(m_adapterServer.data(), uid, false);
        switcher.execute();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::switchSpindelOff: unknown error");
        this->setLastError(ROUTER_ERROR);
    }
}

void MachineTool::onRepository_ErrorOccurred(ERROR_CODE code)
{
    this->setLastError(code);
}

void MachineTool::onServer_U1Connected()
{
    m_repository->setU1ConnectState(true);
}

void MachineTool::onServer_U1Disconnected()
{
    m_repository->setU1ConnectState(false);
}

void MachineTool::onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, unsigned int workflowState, ERROR_CODE lastError)
{
    this->setLastError(lastError);
    m_repository->setU1Sensors(sensors);
    m_repository->setU1Devices(devices);
    m_repository->setU1WorkflowState(workflowState);
}

void MachineTool::onServer_ErrorOccurred(ERROR_CODE errorCode)
{
    this->setLastError(errorCode);
}

void MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged()
{
    try
    {
        bool u1 = m_repository->m_u1Adapter->connectionState();
        bool u2 = true;

        if(u1 && u2)
        {
            this->setLastError(OK);
        }
        else
        {
            if(!u1 && !u2)
            {
                this->setLastError(DISCONNECTED);
            }
            else
            {
                if(u1 == false)
                {
                    this->setLastError(DISCONNECTED);
                }

                if(u2 == false)
                {
                    this->setLastError(DISCONNECTED);
                }
            }
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
    qDebug() << "Workflow state of u1 adapters is u1 = " << m_repository->m_u1Adapter->workflowState()
             << "and u2 = "<< m_repository->m_u2Adapter->workflowState() << "now";
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
        QColor led = QColor(SmlColors::white());
        if(state)
        {
            led = m_repository->getSensor(sensorUid).getColor();
        }
        emit this->sensorStateChanged(sensorUid, led);
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
