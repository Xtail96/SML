#ifndef GCODESMONITOR_H
#define GCODESMONITOR_H

#include <QObject>

#include "models/types/gcodes/gcodesfilesmanager/gcodesfilesmanager.h"

class GCodesMonitor : public QObject
{
    Q_OBJECT
public:
    explicit GCodesMonitor(GCodesFilesManager* gcodesManager, QObject *parent = nullptr);

signals:
    void filePathUpdated(QString);
    void fileContentUpdated(QString);

protected slots:
    void onGCodesManager_FilePathUpdated(QString filePath);
    void onGCodesManager_FileContentUpdated(QString data);
};

#endif // GCODESMONITOR_H
