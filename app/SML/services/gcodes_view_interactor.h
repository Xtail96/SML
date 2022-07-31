#ifndef GCODESVIEWINTERACTOR_H
#define GCODESVIEWINTERACTOR_H

#include <QString>
#include <QProcess>
#include <QMessageBox>
#include "./common/settings/settings_manager.h"

class GCodesViewInteractor
{
public:
    GCodesViewInteractor();

    static void execute(QStringList gcodes, QObject *parent = nullptr);
    static void execute(QString gcodesFileName, QObject *parent = nullptr);

private:
    static QString getViewerPath();
};

#endif // GCODESVIEWINTERACTOR_H
