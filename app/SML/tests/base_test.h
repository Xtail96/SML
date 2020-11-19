#ifndef BASETEST_H
#define BASETEST_H

#include <QObject>
#include <QTest>

class BaseTest : public QObject
{
    Q_OBJECT
public:
    explicit BaseTest(QObject *parent = nullptr);

private slots:
    void initTestCase();

    static void messageHandler(QtMsgType, const QMessageLogContext&, const QString &);
};

#endif // BASETEST_H
