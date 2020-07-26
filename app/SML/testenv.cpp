#include "testenv.h"

TestEnv::TestEnv(QObject *parent) :
    QObject(parent),
    s(this),
    m(this),
    d(this),
    r(&m, &d, this)
{
    qDebug() << "server is started =" << s.startServer(1234);

    QObject::connect(&s, &AdapterGateway::newConnection, this, [=](QWebSocket* client) {
        r.addClient(client);

        //m.addClient(client);

        //m.sendMessage("test1");
        //s.stopServer();

        //for(int i = 0; i < 100; i++)
            //m.sendMessage(QString("test" + QString::number(i)).toUtf8());

    });
}
