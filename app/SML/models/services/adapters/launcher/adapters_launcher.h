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

    void startAdapters(QString u1AdapterPath, QString u2AdapterPath);
    void stopAdapters();

private:
    QProcess m_u1AdapterProcess;
    QProcess m_u2AdapterProcess;


signals:

public slots:
};

#endif // ADAPTERS_LAUNCHER_H
