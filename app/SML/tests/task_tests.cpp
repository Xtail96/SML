#include "task_tests.h"

TaskTests::TaskTests(QObject *parent) : BaseTest(parent) {}

void TaskTests::testSerializeOneLineGCode()
{
    QString input = "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1";
    Task t(input);

    QString expected = "G1 X10 Y100.5 Z0 A0 B0 F300 M1";
    QString actual = t.serialize();
    QCOMPARE(actual, expected);
}

void TaskTests::testSerializeMultiLineGCode()
{
    QStringList input =  {
        "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1",
        "G0 X100, Y100, Z50"
    };
    Task t(input.join("\n"));

    QStringList expected = {
            "G1 X10 Y100.5 Z0 A0 B0 F300 M1",
            "G0 X100 Y100 Z50"
    };
    QString actual = t.serialize();
    QCOMPARE(actual, expected.join("\n"));
}

void TaskTests::testBlocksCountOneLine()
{
    QString input = "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1";
    Task t(input);
    QCOMPARE(t.blocksCount(), 1);
}

void TaskTests::testBlocksCountMultiline()
{
    QStringList input =  {
        "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1",
        "G0 X100, Y100, Z50"
    };
    Task t(input.join("\n"));
    QCOMPARE(t.blocksCount(), 2);
}

void TaskTests::testGetBlockOneLine()
{
    QString input = "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1";
    Task t(input);

    QString expected = "G1 X10 Y100.5 Z0 A0 B0 F300 M1";
    QString actual = t.block(0);
    QCOMPARE(actual, expected);
}

void TaskTests::testGetBlockMultiline()
{
    QStringList input =  {
        "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1",
        "G0 X100, Y100, Z50"
    };
    Task t(input.join("\n"));

    QString expected = "G0 X100 Y100 Z50";
    QString actual = t.block(1);
    QCOMPARE(actual, expected);
}

void TaskTests::testGetBlockIdPositive()
{
    QString input = "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1";
    Task t(input);

    QString expected = "G1";
    QString actual = t.blockId(0);
    QCOMPARE(actual, expected);
}

void TaskTests::testGetBlockIdNegative()
{
    QString input = "X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1";
    Task t(input);

    QString expected = "";
    QString actual = t.blockId(0);
    QCOMPARE(actual, expected);
}

void TaskTests::testGetBlockAxesArgs()
{
    QString input = "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1";
    Task t(input);

    QMap<QString, QVariant> expected = {
        { "X", 10 },
        { "Y", 100.5 },
        { "Z", 0 },
        { "A", 0 },
        { "B", 0 }
    };

    QMap<QString, QVariant> actual = t.blockAxesArgs(0);
    QCOMPARE(actual.size(), expected.size());

    for(QString key : actual.keys())
    {
        QCOMPARE(expected.contains(key), true);
        QCOMPARE(actual.find(key).value(), expected.find(key).value());
    }
}

void TaskTests::testGetBlockFeedrate()
{
    QString input = "G1 X10.0 Y100.5 Z0.0 A0.0 B0.0 F300 M1";
    Task t(input);

    QString expected = "F300";
    QString actual = t.blockFeedrate(0);
    QCOMPARE(actual, expected);
}
