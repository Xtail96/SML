#include "gcodes_monitor.h"

GCodesMonitor::GCodesMonitor(GCodesFileManager *gcodesManager, QObject *parent) : QObject(parent)
{
    QObject::connect(gcodesManager, SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesManager_FilePathUpdated(QString)));
    QObject::connect(gcodesManager, SIGNAL(fileContentUpdated(QString)), this, SLOT(onGCodesManager_FileContentUpdated(QString)));
}

void GCodesMonitor::onGCodesManager_FilePathUpdated(QString filePath)
{
    emit filePathUpdated(filePath);
}

void GCodesMonitor::onGCodesManager_FileContentUpdated(QString data)
{
    emit fileContentUpdated(data);
}
