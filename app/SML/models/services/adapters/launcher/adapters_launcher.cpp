#include "adapters_launcher.h"

AdaptersLauncher::AdaptersLauncher(QObject *parent) :
    QObject(parent),
    m_u1AdapterProcess(this),
    m_u2AdapterProcess(this)
{

}

void AdaptersLauncher::startAdapters(QString u1AdapterPath, QString u2AdapterPath)
{
    qDebug() << "AdaptersLauncher::startAdapters: try to start adapters U1 =" << u1AdapterPath << "U2 =" << u2AdapterPath;
    if(!m_u1AdapterProcess.isOpen())
    {
        qDebug() << "AdaptersLauncher::startAdapters: try to start u1";
        m_u1AdapterProcess.start(u1AdapterPath);
    }

    if(!m_u2AdapterProcess.isOpen())
    {
        qDebug() << "AdaptersLauncher::startAdapters: try to start u2";
        m_u2AdapterProcess.start(u2AdapterPath);
    }
}

void AdaptersLauncher::stopAdapters()
{
    qDebug() << "AdaptersLauncher::stopAdapters: try to stop adapters";
    if(m_u1AdapterProcess.isOpen())
    {
        qDebug() << "AdaptersLauncher::stopAdapters: try to stop u1";
        m_u1AdapterProcess.kill();
    }

    if(m_u2AdapterProcess.isOpen())
    {
        qDebug() << "AdaptersLauncher::stopAdapters: try to stop u2";
        m_u2AdapterProcess.kill();
    }
}
