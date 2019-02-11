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
    m_lastError(U1_AND_U2_DISCONNECTED) // нет связи со станком
{
    setupConnections();
    startAdapterServer();
}

MachineTool::~MachineTool()
{
    resetConnections();
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
    QObject::connect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, int)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, int)));
    QObject::connect(m_adapterServer.data(), SIGNAL(errorOccured(int)), this, SLOT(onServer_ErrorOccured(int)));

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
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, int)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>, unsigned int, int)));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(errorOccured(int)), this, SLOT(onServer_ErrorOccured(int)));

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
        setLastError(UNEXPECTED_ERROR);
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
        setLastError(UNEXPECTED_ERROR);
    }
}

QStringList MachineTool::getConnectedAdapters()
{
    try
    {
        return m_adapterServer->currentAdapters();
    }
    catch(...)
    {
        setLastError(UNEXPECTED_ERROR);
        return QStringList();
    }
}

QString MachineTool::getAdapterServerPort()
{
    try
    {
        return QString::number(m_adapterServer->port());
    }
    catch (...)
    {
        setLastError(UNEXPECTED_ERROR);
        return QString();
    }

}

int MachineTool::getLastError()
{
    return m_lastError;
}

void MachineTool::setLastError(int value)
{
    m_lastError = value;

    // вызов интерактора-обработчика
    switch (value)
    {
        case OK: break;
        case U1_ADAPTER_DISCONNECTED: break;
        case U2_ADAPTER_DISCONNECTED: break;
        case U1_AND_U2_DISCONNECTED: break;
        case UNEXPECTED_ERROR: break;
        case SYNCHRONISATION_ERROR: break;
    }

    emit errorOccured(m_lastError);
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
        setLastError(UNEXPECTED_ERROR);
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
        setLastError(UNEXPECTED_ERROR);
    }
}

void MachineTool::onServer_U1Connected()
{
    try
    {
        m_repository->setU1ConnectState(true);
    }
    catch(...)
    {
        setLastError(UNEXPECTED_ERROR);
    }
}


void MachineTool::onServer_U1Disconnected()
{
    try
    {
        m_repository->setU1ConnectState(false);
    }
    catch(...)
    {
        setLastError(UNEXPECTED_ERROR);
    }
}

void MachineTool::onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, unsigned int workflowState, int lastError)
{
    try
    {
        m_repository->setU1Sensors(sensors);
        m_repository->setU1Devices(devices);
        m_repository->setU1WorkflowState(workflowState);
        if(lastError != 0)
        {
            setLastError(lastError);
        }
    }
    catch(SynchronizeStateException e)
    {
        qDebug() << "MachineTool::onServer_U1StateChanged:" << e.message();
        setLastError(SYNCHRONISATION_ERROR);
    }
    catch(...)
    {
        setLastError(UNEXPECTED_ERROR);
    }
}

void MachineTool::onServer_ErrorOccured(int errorCode)
{
    setLastError(SERVER_ERROR);
}

void MachineTool::onAdaptersMonitor_AdapterConnectionStateChanged()
{
    try
    {
        bool u1 = m_repository->m_u1Adapter->connectionState();
        bool u2 = true;

        if(u1 && u2)
        {
            setLastError(OK);
        }
        else
        {
            if(!u1 && !u2)
            {
                setLastError(U1_AND_U2_DISCONNECTED);
            }
            else
            {
                if(u1 == false)
                {
                    setLastError(U1_ADAPTER_DISCONNECTED);
                }

                if(u2 == false)
                {
                    setLastError(U2_ADAPTER_DISCONNECTED);
                }
            }
        }
    }
    catch(...)
    {
        setLastError(UNEXPECTED_ERROR);
    }
}

void MachineTool::onAdaptersMonitor_AdapterWorkflowStateChanged()
{
    qDebug() << "Workflow state of u1 adapters is u1 = " << m_repository->m_u1Adapter->workflowState()
             << "and u2 = "<< m_repository->m_u2Adapter->workflowState() << "now";
}

void MachineTool::onPointsMonitor_PointsUpdated()
{
    emit pointsUpdated();
}

void MachineTool::onSensorMonitor_StateChanged(QString sensorName, bool state)
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
            led = m_repository->getSensor(sensorName).getColor();
        }
        emit sensorStateChanged(sensorName, led);
    }
    catch(...)
    {
        setLastError(UNEXPECTED_ERROR);
    }
}

void MachineTool::onSpindelsMonitor_StateChanged(QString index, bool state, size_t rotations)
{
    emit spindelStateChanged(index, state, rotations);
}

void MachineTool::onGCodesMonitor_FilePathUpdated(QString path)
{
    emit gcodesFilePathUpdated(path);
}

void MachineTool::onGCodesMonitor_FileContentUpdated(QStringList content)
{
    emit gcodesFileContentUpdated(content);
}
