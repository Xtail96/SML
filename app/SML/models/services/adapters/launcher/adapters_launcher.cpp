#include "adapters_launcher.h"

AdaptersLauncher::AdaptersLauncher(QObject *parent) :
    QObject(parent),
    m_u1AdapterProcess(new QProcess(this)),
    m_u2AdapterProcess(new QProcess(this))
{

}

void AdaptersLauncher::startAdapters(QString u1AdapterPath, QString u2AdapterPath)
{
    qDebug() << "try to start adapters" << u1AdapterPath << u2AdapterPath;
    if(!m_u1AdapterProcess->isOpen())
    {
        qDebug() << "start u1";
        m_u1AdapterProcess->start(u1AdapterPath);
    }

    if(!m_u2AdapterProcess->isOpen())
    {
        qDebug() << "start u2";
        m_u2AdapterProcess->start(u2AdapterPath);
    }
}

void AdaptersLauncher::stopAdapters()
{
    qDebug() << "try to stop adapters";
    if(m_u1AdapterProcess->isOpen())
    {
        qDebug() << "try to stop u1";
        m_u1AdapterProcess->kill();
    }

    if(m_u2AdapterProcess->isOpen())
    {
        qDebug() << "try to stop u2";
        m_u2AdapterProcess->kill();
    }
}
