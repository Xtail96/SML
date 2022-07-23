#include "websocket_gateway_tests.h"

WebSocketGatewayTests::WebSocketGatewayTests(QObject *parent) : BaseTest(parent) {}

void WebSocketGatewayTests::testOpen()
{
    qint16 port = 1234;
    WebSocketGateway g(this);
    QCOMPARE(g.open(port), true);
    QCOMPARE(g.isOpen(), true);
}

void WebSocketGatewayTests::testClose()
{
    qint16 port = 1234;
    WebSocketGateway g(this);
    QCOMPARE(g.open(port), true);
    QCOMPARE(g.isOpen(), true);
    g.close();
    QCOMPARE(g.isOpen(), false);
}

void WebSocketGatewayTests::testGetPort()
{
    qint16 port = 1234;
    WebSocketGateway g(this);
    QCOMPARE(g.open(port), true);
    QCOMPARE(g.port(), port);
}
