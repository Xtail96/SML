#include "adapters_launcher.h"

AdaptersLauncher::AdaptersLauncher(QObject *parent) :
    QObject(parent),
    m_deviceAdapterPath(""),
    m_motionAdapterPath(""),
    m_deviceAdapterProcess(this),
    m_motionAdapterProcess(this)
{
    SettingsManager s;
    m_deviceAdapterPath= s.get("ExternalTools", "DeviceAdapter").toString();
    m_motionAdapterPath = s.get("ExternalTools", "MotionAdapter").toString();
}

AdaptersLauncher::~AdaptersLauncher()
{
    this->stopAdapters();
}

void AdaptersLauncher::startAdapters()
{
    qInfo() << "try to start adapters Device Adapter =" << m_deviceAdapterPath << "Motion Adapter =" << m_motionAdapterPath;
    if(!m_deviceAdapterProcess.isOpen())
    {
        qInfo() << "try to start device adapter";
        m_deviceAdapterProcess.start(m_deviceAdapterPath);
    }

    if(!m_motionAdapterProcess.isOpen())
    {
        qInfo() << "try to start motion adapter";
        m_motionAdapterProcess.start(m_motionAdapterPath);
    }
}

void AdaptersLauncher::stopAdapters()
{
    qInfo() << "try to stop adapters";
    if(m_deviceAdapterProcess.isOpen())
    {
        qInfo() << "try to stop device adapter";
        m_deviceAdapterProcess.kill();
        m_deviceAdapterProcess.waitForFinished(-1);
    }

    if(m_motionAdapterProcess.isOpen())
    {
        qInfo() << "try to stop motion adapter";
        m_motionAdapterProcess.kill();
        m_motionAdapterProcess.waitForFinished(-1);
    }
}
