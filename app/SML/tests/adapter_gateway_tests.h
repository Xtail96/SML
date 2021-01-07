#ifndef ADAPTERGATEWAYTESTS_H
#define ADAPTERGATEWAYTESTS_H

#include "./base_test.h"
#include "./models/hardware/controllers/adapters/adapter_gateway.h"

class AdapterGatewayTests : public BaseTest
{
    Q_OBJECT
public:
    AdapterGatewayTests(QObject *parent = nullptr);

private slots:
    void testOpen();
    void testClose();
    void testGetPort();
};

#endif // ADAPTERGATEWAYTESTS_H
