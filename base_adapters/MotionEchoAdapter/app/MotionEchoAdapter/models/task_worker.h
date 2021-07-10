#ifndef TASKWORKER_H
#define TASKWORKER_H

#include <QObject>

#include "./motion_task.h"

class TaskWorker : public QObject
{
    Q_OBJECT
public:
    explicit TaskWorker(MotionControllerState state,
                        QtJson::JsonObject message,
                        QObject *parent = nullptr);
    ~TaskWorker();

private:
    MotionControllerState m_state;
    QtJson::JsonObject m_message;

signals:
    void finished();
    void currentStateChanged(MotionControllerState s);

public slots:
    void process();
    void stop();
};

#endif // TASKWORKER_H
