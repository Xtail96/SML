#include "adapter_gateway_tests.h"

AdapterGatewayTests::AdapterGatewayTests(QObject *parent) : BaseTest(parent) {}

void AdapterGatewayTests::testOpen()
{
    qint16 port = 1234;
    AdapterGateway g(this);
    QCOMPARE(g.open(port), true);
    QCOMPARE(g.isOpen(), true);
}

void AdapterGatewayTests::testClose()
{
    qint16 port = 1234;
    AdapterGateway g(this);
    QCOMPARE(g.open(port), true);
    QCOMPARE(g.isOpen(), true);
    g.close();
    QCOMPARE(g.isOpen(), false);
}

void AdapterGatewayTests::testGetPort()
{
    qint16 port = 1234;
    AdapterGateway g(this);
    QCOMPARE(g.open(port), true);
    QCOMPARE(g.port(), port);
}
