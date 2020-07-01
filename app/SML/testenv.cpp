#include "testenv.h"

TestEnv::TestEnv(QObject *parent) :
    QObject(parent),
    s(this),
    m(this)
{
    qDebug() << "server is started =" << s.startServer(1234);

    QObject::connect(&s, &AdapterServer::newConnection, this, [=](QWebSocket* client) {
        m.addClient(client);
    });
}
