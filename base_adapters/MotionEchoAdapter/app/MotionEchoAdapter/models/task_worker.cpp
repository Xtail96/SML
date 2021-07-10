#include "task_worker.h"

TaskWorker::TaskWorker(MotionControllerState state,
                       QtJson::JsonObject message,
                       QObject *parent) :
    QObject(parent),
    m_state(state),
    m_message(message)
{
}

TaskWorker::~TaskWorker()
{
}

void TaskWorker::process()
{
    MotionTask* task = new MotionTask(m_state, this);
    QObject::connect(task, &MotionTask::currentStateChanged, this, [=](MotionControllerState state) {
        emit this->currentStateChanged(state);
    });

    task->execute(m_message);
    emit this->finished();
    task->deleteLater();
    return;
}

void TaskWorker::stop()
{
    qDebug() << "stop current task";
}
