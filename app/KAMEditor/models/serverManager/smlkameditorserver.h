#ifndef SMLKAMEDITORSERVER_H
#define SMLKAMEDITORSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

#include "models/structs.h"
#include "models/settingsmanager/settingsmanager.h"

enum Role {U1Adapter, U2Adapter};

class SMLKAMEditorServer : public QObject
{
    Q_OBJECT
public:
    explicit SMLKAMEditorServer(SettingsManager *settingsManager = nullptr, QObject *parent = nullptr);
    ~SMLKAMEditorServer();

protected:
    QWebSocketServer *m_server;
    qint16 m_port;

    QWebSocket *m_u1Adapter;
    QWebSocket *m_u2Adapter;

    QList<QWebSocket *> m_unregisteredConnections;
    bool m_debug;
signals:
    void newConnection();

    void u1Connected();
    void u1Disconnected();
    void u2Connected();
    void u2Disconnected();

    void byteMessageReceived(QByteArray message);

public slots:
    void start();
    void stop();
    void sendMessageToU1(QByteArray message);

protected slots:
    void setup(SettingsManager* sm);
    void closeServer();
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void registerConnection(QWebSocket *connection, Role role);

};

#endif // SMLKAMEDITORSERVER_H
