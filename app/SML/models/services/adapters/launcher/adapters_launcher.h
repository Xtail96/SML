#ifndef ADAPTERS_LAUNCHER_H
#define ADAPTERS_LAUNCHER_H

#include <QObject>
#include <QProcess>
#include <QScopedPointer>
#include <QDebug>

class AdaptersLauncher : public QObject
{
    Q_OBJECT
public:
    explicit AdaptersLauncher(QObject *parent = nullptr);

    void startAdapters(QString deviceAdapterPath, QString motionAdapterPath);
    void stopAdapters();

private:
    QProcess m_deviceAdapterProcess;
    QProcess m_motionAdapterProcess;


signals:

public slots:
};

#endif // ADAPTERS_LAUNCHER_H
