#ifndef MOTIONTASK_H
#define MOTIONTASK_H

#include <QObject>
#include <QTest>
#include "math.h"
#include "libs/jsonparser/json.h"

#include "./structs.h"

class MotionTask : public QObject
{
    Q_OBJECT
public:
    explicit MotionTask(MotionControllerState state, bool debugMode = false, QObject* parent = nullptr);
    void execute(QtJson::JsonObject parsedMessage);
    MotionControllerState getCurrentState();
    void stop();

private:
    MotionControllerState m_state;
    bool m_terminationRequested;
    bool m_debugMode;
    void debugMessage(QString msg);
    QMap<QString, double> getCurrentPositionOffset(QMap<QString, double> targetPosition);
    int getStepsCount(QMap<QString, double> positionOffset);

signals:
    void currentStateChanged(MotionControllerState state);

};

#endif // MOTIONTASK_H