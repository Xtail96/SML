#include "gcodes_monitor.h"

GCodesMonitor::GCodesMonitor(GCodesFileManager &gcodesManager, QObject *parent) : QObject(parent)
{
    QObject::connect(&gcodesManager, SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesManager_FilePathUpdated(QString)));
    QObject::connect(&gcodesManager, SIGNAL(fileContentUpdated(QStringList)), this, SLOT(onGCodesManager_FileContentUpdated(QStringList)));
}

void GCodesMonitor::onGCodesManager_FilePathUpdated(QString filePath)
{
    emit filePathUpdated(filePath);
}

void GCodesMonitor::onGCodesManager_FileContentUpdated(QStringList data)
{
    emit fileContentUpdated(data);
}
