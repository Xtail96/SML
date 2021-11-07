#include "motion_task.h"

MotionTask::MotionTask(MotionControllerState state, bool debugMode, QObject *parent):
    QObject(parent),
    m_state(state),
    m_terminationRequested(false),
    m_debugMode(debugMode)
{

}

QMap<QString, double> MotionTask::getCurrentPositionOffset(QMap<QString, double> targetPosition)
{
    QMap<QString, double> positionsDifference = {};
    for(auto key : targetPosition.keys())
    {
        double difference = targetPosition[key] - m_state.getAxisPosition(key);
        positionsDifference.insert(key, difference);
    }
    return positionsDifference;
}

int MotionTask::getStepsCount(QMap<QString, double> positionOffset)
{
    QList<double> offsets = positionOffset.values();
    for(auto& offset : offsets)
        offset = fabs(offset);
    std::sort(offsets.begin(), offsets.end());
    double maxOffset = offsets.last();
    return (maxOffset >= 1000) ? int(maxOffset): 10;
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
        QMap<QString, double> targetPosition = {};
        for(auto axisId : axesArgumentsRaw.keys())
        {
            bool ok = false;
            double value = axesArgumentsRaw[axisId].toDouble(&ok);
            if(!ok)
                continue;
            targetPosition.insert(axisId, value);
        }

        // calculate increments
        QMap<QString, double> positionOffset = this->getCurrentPositionOffset(targetPosition);
        int stepsCount = this->getStepsCount(positionOffset);
        QMap<QString, double> axesSteps = {};
        for(auto axis : positionOffset.keys())
        {
            double step = positionOffset[axis] / stepsCount;
            axesSteps.insert(axis, step);
        }

        // simulate move
        for(int i = 0; i < stepsCount; i++)
        {
            for(auto key : positionOffset.keys())
            {
                if(m_terminationRequested)
                {
                    m_state.setWorkflowState(0);
                    emit this->currentStateChanged(m_state);
                    return;
                }
                double newAxisPosition = m_state.getAxisPosition(key) + axesSteps[key];
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

