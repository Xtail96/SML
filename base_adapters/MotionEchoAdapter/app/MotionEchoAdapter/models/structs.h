#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>
#include <vector>

#include <QDebug>

typedef unsigned char byte;
typedef std::vector<byte> byte_array;


struct MotionControllerState
{
private:
    QMap<QString, double> m_positions;
    int m_lastErrorCode;
    int m_workflowState;
public:
    MotionControllerState(int errorCode, int workflowCode)
    {
        m_positions = {};
        m_lastErrorCode = errorCode;
        m_workflowState = workflowCode;
    }

    ~MotionControllerState() {}

    byte getLastError()
    {
        return m_lastErrorCode;
    }

    void setLastError(byte value)
    {
        m_lastErrorCode = value;
    }

    int getWorkflowState()
    {
        return m_workflowState;
    }

    void setWorkflowState(int value)
    {
        m_workflowState = value;
    }

    int getAxesCount()
    {
        return m_positions.size();
    }

    QStringList getAxisesKeys()
    {
        return m_positions.keys();
    }

    double getAxisPosition(QString key)
    {
        if(!m_positions.contains(key))
            throw std::invalid_argument("Unknown axis name " + key.toStdString());

        return m_positions[key];
    }

    void setAxisPosition(QString key, double value)
    {
        if(!m_positions.contains(key))
            throw std::invalid_argument("Unknown axis name " + key.toStdString());

        this->removeAxisPosition(key);
        this->addAxisPosition(key, value);
    }

    void addAxisPosition(QString key, double value)
    {
        m_positions.insert(key, value);
    }

    void removeAxisPosition(QString key)
    {
        if(!m_positions.contains(key))
            throw std::invalid_argument("Unknown axis name " + key.toStdString());

        m_positions.remove(key);
    }
};

#endif // STRUCTS_H
