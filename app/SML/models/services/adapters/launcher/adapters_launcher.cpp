#include "adapters_launcher.h"

AdaptersLauncher::AdaptersLauncher(QObject *parent) :
    QObject(parent),
    m_deviceAdapterProcess(this),
    m_motionAdapterProcess(this)
{

}

void AdaptersLauncher::startAdapters(QString deviceAdapterPath, QString motionAdapterPath)
{
    qInfo() << "try to start adapters Device Adapter =" << deviceAdapterPath << "Motion Adapter =" << motionAdapterPath;
    if(!m_deviceAdapterProcess.isOpen())
    {
        qInfo() << "try to start device adapter";
        m_deviceAdapterProcess.start(deviceAdapterPath);
    }

    if(!m_motionAdapterProcess.isOpen())
    {
        qInfo() << "try to start motion adapter";
        m_motionAdapterProcess.start(motionAdapterPath);
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
