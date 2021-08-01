#include "motion_task.h"

MotionTask::MotionTask(MotionControllerState state, bool debugMode, QObject *parent):
    QObject(parent),
    m_state(state),
    m_terminationRequested(false),
    m_debugMode(debugMode)
{

}

void MotionTask::execute(QtJson::JsonObject parsedMessage)
{
    this->debugMessage("start processing");
    m_terminationRequested = false;
    m_state.setWorkflowState(1);
    QtJson::JsonArray blocks = parsedMessage["blocks"].toList();
    for(int i = 0; i < blocks.length(); i++)
    {
        QtJson::JsonObject block = blocks[i].toMap();
        QtJson::JsonObject detailedInfo = block["detailedInfo"].toMap();
        QtJson::JsonObject axesArgumentsRaw = detailedInfo["axesArguments"].toMap();
        QMap<QString, double> axesArgumentsMap = {};
        for(auto axisId : axesArgumentsRaw.keys())
        {
            bool ok = false;
            double value = axesArgumentsRaw[axisId].toDouble(&ok);
            if(!ok) continue;
            axesArgumentsMap.insert(axisId, value);
        }

        // calculate increments
        QStringList axisArgumentsKeys = axesArgumentsMap.keys();
        int stepsCount = 10;
        QMap<QString, double> stepIncrements = {};
        for(auto key : axisArgumentsKeys)
        {
            double diff = (axesArgumentsMap[key] - m_state.getAxisPosition(key));
            double stepByAxis = diff / stepsCount;
            stepIncrements.insert(key, stepByAxis);
        }

        // simulate move
        for(int i = 0; i < stepsCount; i++)
        {
            for(auto key : axisArgumentsKeys)
            {
                if(m_terminationRequested)
                {
                    m_state.setWorkflowState(0);
                    emit this->currentStateChanged(m_state);
                    return;
                }
                double newAxisPosition = m_state.getAxisPosition(key) + stepIncrements[key];
                m_state.setAxisPosition(key, newAxisPosition);
            }

            this->debugMessage(QString::number((i+1) * 10) + "% done");
            emit this->currentStateChanged(m_state);

            // wait
            QTest::qWait(100);
        }
    }
    this->debugMessage("finish processing");
    m_state.setWorkflowState(0);
}

MotionControllerState MotionTask::getCurrentState()
{
    return m_state;
}

void MotionTask::stop()
{
    m_terminationRequested = true;
}

void MotionTask::debugMessage(QString msg)
{
    if(m_debugMode)
        qDebug() << "MotionTask::" + msg;
}

