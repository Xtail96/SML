#ifndef ADAPTERS_LAUNCHER_H
#define ADAPTERS_LAUNCHER_H

#include <QObject>
#include <QProcess>
#include <QScopedPointer>
#include <QDebug>

#include "models/settings_manager/settings_manager.h"

class AdaptersLauncher : public QObject
{
    Q_OBJECT
public:
    explicit AdaptersLauncher(QObject *parent = nullptr);
    ~AdaptersLauncher();

    void startAdapters();
    void stopAdapters();

private:
    QString m_deviceAdapterPath;
    QString m_motionAdapterPath;

    QProcess m_deviceAdapterProcess;
    QProcess m_motionAdapterProcess;


signals:

public slots:
};

#endif // ADAPTERS_LAUNCHER_H
