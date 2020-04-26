#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_serialPortReadBuffer(QByteArray()),
    m_axes(QList<AxisState>())
{
    this->loadSettings();
}

QtJson::JsonObject Repository::currentState()
{
    QtJson::JsonObject result = {};
    QtJson::JsonObject u2State = {};

    int workflowState = 0;
    for(auto axis : m_axes)
    {
        qDebug() << axis.getId() << "motor is moving" << axis.getMotor().isMoving();
        if(axis.getMotor().isMoving())
        {
            workflowState = 1;
            break;
        }
    }

    qDebug() << "workflowState" << workflowState;

    u2State["workflowState"] = workflowState;
    u2State["lastError"] = 0;
    u2State["axesCount"] = m_axes.length();

    QtJson::JsonArray axesState = {};
    for(auto axis : m_axes)
    {
        axesState.append(axis.currentState());
    }
    u2State["axes"] = axesState;
    result["u2State"] = u2State;
    return result;
}

void Repository::updateCurrentState(QtJson::JsonObject serialPortMessage)
{
    int motorId = serialPortMessage["motor"].toInt();
    bool isMoving = serialPortMessage["isMoving"].toBool();
    int task = serialPortMessage["task"].toInt();
    int progress = serialPortMessage["progress"].toInt();
    bool taskCompleted = serialPortMessage["taskCompleted"].toBool();
    bool invertDirection = serialPortMessage["invertedDirection"].toBool();

    for(auto& axis : m_axes)
    {
        if(axis.getMotor().id() != motorId) continue;

        axis.getMotor().setCurrentProgress(invertDirection ? -1 * progress : progress);
    }
}

void Repository::loadSettings()
{
    try
    {
        m_serialPortName = "tty.usbmodem14101";
        m_axes.append(AxisState("X", MotorState(0, 1)));
    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();
    }
}
