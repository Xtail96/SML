#include "sensorsbuffer.h"

SensorsBuffer::SensorsBuffer(QObject *parent) : QObject(parent)
{

}

void SensorsBuffer::updateBuffer(byte_array value)
{
    if(value.size() == m_buffer.size())
    {
        m_buffer = value;
    }
    else
    {
        qDebug() << "can not update buffer" << m_buffer.size() << " != " << value.size();
    }
}

bool SensorsBuffer::isPortStateChanged(byte currentState, byte newState)
{
    bool sensorsStateChanged = false;
    if(currentState != newState)
    {
        sensorsStateChanged = true;
    }
    return sensorsStateChanged;
}

bool SensorsBuffer::getInputState(QString plateName, unsigned int portNumber, unsigned int inputNumber) const
{
    bool voltage = false;
    if(plateName == "portal")
    {
        voltage = checkPortalSensorState(portNumber, inputNumber);
    }
    else
    {
        if(plateName == "u1")
        {
            voltage = checkU1SensorState(portNumber, inputNumber);
        }
        else
        {
            if(plateName == "u2")
            {
                // todo
            }
        }
    }
    return voltage;
}

void SensorsBuffer::resetBuffer(size_t size)
{
    m_buffer = byte_array(size, 0);
}

bool SensorsBuffer::standardInputStateCheck(size_t inputNumber, byte portState) const
{
    bool voltage = true;

    byte tmp = portState;
    // сдвигаем все биты влево, чтобы исключить все биты слева, а нужный бит стоял в старшем разряде
    tmp = tmp << (7-inputNumber);

    // сдвигаем все биты вправо, чтобы все биты слева стали нулями, а нужный бит находился в младшем разряде
    tmp = tmp >> 7;

    if(tmp == 0x00)
    {
        voltage = false;
    }
    else
    {
        if(tmp == 0x01)
        {
            voltage = true;
        }
    }

    return voltage;
}

bool SensorsBuffer::checkPortalSensorState(unsigned int portNumber, unsigned int inputNumber) const
{
    bool voltage = true;

    switch(portNumber) {
    case 0:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[0]);
        break;
    }
    case 1:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[1]);
        break;
    }
    case 2:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[2]);
        break;
    }
    case 3:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[3]);
        break;
    }
    case 4:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[4]);
        break;
    }
    case 5:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[5]);
        break;
    }
    case 6:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[6]);
        break;
    }
    case 7:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[7]);
        break;
    }
    default:
        break;
    }
    return voltage;
}

bool SensorsBuffer::checkU1SensorState(unsigned int portNumber, unsigned int inputNumber) const
{
    bool voltage = true;

    switch(portNumber) {
    case 0:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[8]);
        break;
    }
    case 1:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[9]);
        break;
    }
    case 2:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[10]);
        break;
    }
    case 3:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[11]);
        break;
    }
    case 4:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[12]);
        break;
    }
    case 5:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[13]);
        break;
    }
    case 6:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[14]);
        break;
    }
    case 7:
    {
        voltage = standardInputStateCheck(inputNumber, m_buffer[15]);
        break;
    }
    default:
        break;
    }
    return voltage;
}
