#ifndef WEBSOCKETGATEWAYTESTS_H
#define WEBSOCKETGATEWAYTESTS_H

#include "./base_test.h"
#include "./common/websockets/websocket_gateway.h"

class WebSocketGatewayTests : public BaseTest
{
    Q_OBJECT
public:
    WebSocketGatewayTests(QObject *parent = nullptr);

private slots:
    void testOpen();
    void testClose();
    void testGetPort();
};

#endif // WEBSOCKETGATEWAYTESTS_H
