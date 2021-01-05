#ifndef AXISTESTS_H
#define AXISTESTS_H

#include "./base_test.h"
#include "../models/hardware/controllers/motion_controller/axis.h"

class AxisTests : public BaseTest
{
    Q_OBJECT
public:
    AxisTests(QObject *parent = nullptr);

private slots:
    void testDecorateId();

    void testIdFromStr();

    void testCurrentPositionFromZero();

    void testCurrentPositionFromBase();

    void testZeroPosition();

    void testParkPosition();

    void testGetId();

    void testGetDecoratedId();

    void testOperatorEqual();

    void testOperatorNotEqual();

    void testOperatorGreatherOrEqual();

    void testOperatorLessOrEqual();

    void testOperatorGreather();

    void testOperatorLess();

    void testIsPosEqual();
};

#endif // AXISTESTS_H
