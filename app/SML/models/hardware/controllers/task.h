#ifndef TASK_H
#define TASK_H

#include <QStringList>
#include <QMap>
#include <QVariant>

#include "libs/gpr/gcode_program.h"
#include "libs/gpr/parser.h"

const QStringList GCODE_AXIS_KEYS = {"x", "y", "z", "a", "b", "c", "u", "v", "w"};
const QString GCODE_ID_KEY = "g";
const QString GCODE_FEEDRATE_KEY = "f";
const QString MCODE_KEY = "m";

class Task
{
public:
    Task(QString gcode);

    QString serialize();

    int blocksCount() const;

    QString block(int index);

    QString blockId(int index);

    QMap<QString, QVariant> blockAxesArgs(int index);

    QString blockFeedrate(int index);

    QString blockMCode(int index);

private:
    gpr::gcode_program m_gcode;

    void removeEmptyBlocks();

    static QString strAddr(gpr::addr addr);

    bool chunkExists(gpr::block block, QString word);

    gpr::chunk getChunk(gpr::block block, QString word);
};

#endif // TASK_H
