#include "motion_task.h"

MotionTask::MotionTask(MotionControllerState state, QObject *parent):
    QObject(parent),
    m_state(state)
{

}

void MotionTask::execute(QtJson::JsonObject parsedMessage)
{
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
                double newAxisPosition = m_state.getAxisPosition(key) + stepIncrements[key];
                m_state.setAxisPosition(key, newAxisPosition);
            }

            qDebug() << "send state" << i;
            emit this->currentStateChanged(m_state);

            // wait
            QTest::qWait(100);
        }
    }
    qDebug() << "finish processing";
    m_state.setWorkflowState(0);
}

MotionControllerState MotionTask::getCurrentState()
{
    return m_state;
}

