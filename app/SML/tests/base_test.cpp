#include "base_test.h"

BaseTest::BaseTest(QObject *parent) : QObject(parent){}

void BaseTest::initTestCase()
{
    qInstallMessageHandler(BaseTest::messageHandler);
}

void BaseTest::messageHandler(QtMsgType, const QMessageLogContext &, const QString &){}
