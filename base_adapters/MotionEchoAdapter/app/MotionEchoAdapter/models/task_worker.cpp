#include "task_worker.h"

TaskWorker::TaskWorker(MotionControllerState state,
                       QtJson::JsonObject message, bool debugMode,
                       QObject *parent) :
    QObject(parent),
    m_state(state),
    m_message(message),
    m_task(nullptr),
    m_debugMode(debugMode)
{
}

TaskWorker::~TaskWorker()
{
    this->debugMessage("~TaskWorker called");
    m_task->deleteLater();
}

void TaskWorker::debugMessage(QString msg)
{
    if(m_debugMode)
        qDebug() << "TaskWorker::" + msg;
}

void TaskWorker::process()
{
    if(m_task != nullptr)
    {
        this->debugMessage("other task is already running");
        return;
    }

    this->debugMessage("start a new task");
    m_task = new MotionTask(m_state, m_debugMode, this);
    QObject::connect(m_task, &MotionTask::currentStateChanged, this, [=](MotionControllerState state) {
        emit this->currentStateChanged(state);
    });

    m_task->execute(m_message);
    this->debugMessage("finish task");
    emit this->finished();
}

void TaskWorker::stop()
{
    this->debugMessage("stop current task");
    m_task->stop();
}
