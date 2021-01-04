#ifndef TASKTESTS_H
#define TASKTESTS_H

#include "./base_test.h"

#include "./models/hardware/controllers/task.h"

class TaskTests : public BaseTest
{
    Q_OBJECT
public:
    TaskTests(QObject *parent = nullptr);

private slots:
    void testSerializeOneLineGCode();

    void testSerializeMultiLineGCode();

    void testBlocksCountOneLine();

    void testBlocksCountMultiline();

    void testGetBlockOneLine();

    void testGetBlockMultiline();

    void testGetBlockIdPositive();

    void testGetBlockIdNegative();

    void testGetBlockAxesArgs();

    void testGetBlockFeedrate();

    //void testOneLineGCodeParsing();

    //void testMultilineGCodeParsing();

    //void testFullGCodeBlockParsing();

    //void testOneAxisGcodeBlockParsing();



};

#endif // TASKTESTS_H
