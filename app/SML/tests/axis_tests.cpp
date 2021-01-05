#include "axis_tests.h"

AxisTests::AxisTests(QObject *parent) : BaseTest(parent) {}

void AxisTests::testDecorateId()
{
    QCOMPARE(Axis::decorateId(Axis::Id::X), "X");
    QCOMPARE(Axis::decorateId(Axis::Id::Y), "Y");
    QCOMPARE(Axis::decorateId(Axis::Id::Z), "Z");
    QCOMPARE(Axis::decorateId(Axis::Id::A), "A");
    QCOMPARE(Axis::decorateId(Axis::Id::B), "B");
    QCOMPARE(Axis::decorateId(Axis::Id::C), "C");
    QCOMPARE(Axis::decorateId(Axis::Id::U), "U");
    QCOMPARE(Axis::decorateId(Axis::Id::V), "V");
    QCOMPARE(Axis::decorateId(Axis::Id::W), "W");
}

void AxisTests::testIdFromStr()
{
    QCOMPARE(Axis::idFromStr("X"), Axis::Id::X);
    QCOMPARE(Axis::idFromStr("x"), Axis::Id::X);

    QCOMPARE(Axis::idFromStr("Y"), Axis::Id::Y);
    QCOMPARE(Axis::idFromStr("y"), Axis::Id::Y);

    QCOMPARE(Axis::idFromStr("Z"), Axis::Id::Z);
    QCOMPARE(Axis::idFromStr("z"), Axis::Id::Z);

    QCOMPARE(Axis::idFromStr("A"), Axis::Id::A);
    QCOMPARE(Axis::idFromStr("a"), Axis::Id::A);

    QCOMPARE(Axis::idFromStr("B"), Axis::Id::B);
    QCOMPARE(Axis::idFromStr("b"), Axis::Id::B);

    QCOMPARE(Axis::idFromStr("C"), Axis::Id::C);
    QCOMPARE(Axis::idFromStr("c"), Axis::Id::C);

    QCOMPARE(Axis::idFromStr("U"), Axis::Id::U);
    QCOMPARE(Axis::idFromStr("u"), Axis::Id::U);

    QCOMPARE(Axis::idFromStr("V"), Axis::Id::V);
    QCOMPARE(Axis::idFromStr("v"), Axis::Id::V);

    QCOMPARE(Axis::idFromStr("W"), Axis::Id::W);
    QCOMPARE(Axis::idFromStr("w"), Axis::Id::W);
}

void AxisTests::testCurrentPositionFromZero()
{
    Axis::State s(Axis::Id::X, 0.0);
    s.setZeroPosition(50.0);
    s.setCurrentPosition(75.0);
    QCOMPARE(s.currentPositionFromZero(), 25.0);
}

void AxisTests::testCurrentPositionFromBase()
{
    Axis::State s(Axis::Id::X, 0.0);
    s.setZeroPosition(50.0);
    s.setCurrentPosition(75.0);
    QCOMPARE(s.currentPositionFromBase(), 75.0);
}

void AxisTests::testZeroPosition()
{
    Axis::State s(Axis::Id::X, 0.0);
    s.setZeroPosition(50.0);
    QCOMPARE(s.zeroPosition(), 50.0);
}

void AxisTests::testParkPosition()
{
    Axis::State s(Axis::Id::X, 0.0);
    s.setParkPosition(50.0);
    QCOMPARE(s.parkPosition(), 50.0);
}

void AxisTests::testGetId()
{
    Axis::State s(Axis::Id::X, 0.0);
    QCOMPARE(s.id(), Axis::Id::X);
}

void AxisTests::testGetDecoratedId()
{
    Axis::State s(Axis::Id::X, 0.0);
    QCOMPARE(s.decoratedId(), "X");
}

void AxisTests::testOperatorEqual()
{
    Axis::State s1(Axis::Id::X, 0.0);
    Axis::State s2(Axis::Id::X, 10.0);
    Axis::State s3(Axis::Id::Y, 0.0);
    QCOMPARE(s1 == s2, true);
    QCOMPARE(s1 == s3, false);
}

void AxisTests::testOperatorNotEqual()
{
    Axis::State s1(Axis::Id::X, 0.0);
    Axis::State s2(Axis::Id::X, 10.0);
    Axis::State s3(Axis::Id::Y, 0.0);
    QCOMPARE(s1 != s2, false);
    QCOMPARE(s1 != s3, true);
}

void AxisTests::testOperatorGreatherOrEqual()
{
    Axis::State s1(Axis::Id::X, 0.0);
    Axis::State s2(Axis::Id::X, 10.0);
    Axis::State s3(Axis::Id::Y, 0.0);
    QCOMPARE(s1 >= s2, true);
    QCOMPARE(s1 >= s3, false);
    QCOMPARE(s3 >= s1, true);

}

void AxisTests::testOperatorLessOrEqual()
{
    Axis::State s1(Axis::Id::X, 0.0);
    Axis::State s2(Axis::Id::X, 10.0);
    Axis::State s3(Axis::Id::Y, 0.0);
    QCOMPARE(s1 <= s2, true);
    QCOMPARE(s1 <= s3, true);
    QCOMPARE(s3 <= s1, false);
}

void AxisTests::testOperatorGreather()
{
    Axis::State s1(Axis::Id::X, 0.0);
    Axis::State s2(Axis::Id::X, 10.0);
    Axis::State s3(Axis::Id::Y, 0.0);
    QCOMPARE(s1 > s2, false);
    QCOMPARE(s1 > s3, false);
    QCOMPARE(s3 > s1, true);
}

void AxisTests::testOperatorLess()
{
    Axis::State s1(Axis::Id::X, 0.0);
    Axis::State s2(Axis::Id::X, 10.0);
    Axis::State s3(Axis::Id::Y, 0.0);
    QCOMPARE(s1 < s2, false);
    QCOMPARE(s1 < s3, true);
    QCOMPARE(s3 < s1, false);
}

void AxisTests::testIsPosEqual()
{
    QCOMPARE(Axis::State::isPosEqual(10.0, 10.0), true);
    QCOMPARE(Axis::State::isPosEqual(10.0, 10), true);
    QCOMPARE(Axis::State::isPosEqual(10.0, 5), false);
    QCOMPARE(Axis::State::isPosEqual(10.111, 10.112), false);
    QCOMPARE(Axis::State::isPosEqual(10.1111, 10.1112), true);

    QCOMPARE(Axis::State::isPosEqual(10.0, 0.0), false);
    QCOMPARE(Axis::State::isPosEqual(0.0, 0.0), true);
    QCOMPARE(Axis::State::isPosEqual(-10.0, 0.0), false);

    QCOMPARE(Axis::State::isPosEqual(-10.0, -10.0), true);
    QCOMPARE(Axis::State::isPosEqual(-10.0, -10), true);
    QCOMPARE(Axis::State::isPosEqual(-10.0, -5), false);
    QCOMPARE(Axis::State::isPosEqual(-10.111, -10.112), false);
    QCOMPARE(Axis::State::isPosEqual(-10.1111, -10.1112), true);
}
