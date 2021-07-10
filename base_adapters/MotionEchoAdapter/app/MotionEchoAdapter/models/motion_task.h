#ifndef MOTIONTASK_H
#define MOTIONTASK_H

#include <QObject>
#include <QTest>
#include "libs/jsonparser/json.h"

#include "./structs.h"

class MotionTask : public QObject
{
    Q_OBJECT
public:
    explicit MotionTask(MotionControllerState state, QObject* parent);
    void execute(QtJson::JsonObject parsedMessage);
    MotionControllerState getCurrentState();

private:
    MotionControllerState m_state;

signals:
    void currentStateChanged(MotionControllerState state);

};

#endif // MOTIONTASK_H
