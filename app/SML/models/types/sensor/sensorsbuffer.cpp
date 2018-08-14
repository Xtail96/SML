#include "sensorsbuffer.h"

SensorsBuffer::SensorsBuffer(size_t bufferSize, QObject *parent) : QObject(parent)
{
    this->resetBuffer(bufferSize);
}

void SensorsBuffer::resetBuffer(size_t size)
{
    this->m_buffer = byte_array(size, 0x00);
}

void SensorsBuffer::updateBuffer(byte_array value)
{
    if(value.size() == this->m_buffer.size())
    {
        this->m_buffer = value;
    }
    else
    {
        throw std::invalid_argument("invalid buffer size. " +
                                    std::to_string(this->m_buffer.size()) +
                                    " != " + std::to_string(value.size()));
    }
}

bool SensorsBuffer::standardInputStateCheck(size_t inputNumber, byte portState) const
{
    if (inputNumber > 7)
        throw std::invalid_argument("Input should be in range [0; 7]");

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
        else
        {
            throw std::runtime_error("an error has occured during analyze sensor " +
                                     std::to_string(inputNumber) + " " + std::to_string(portState));
        }
    }

    return voltage;
}

bool SensorsBuffer::isPortStateChanged(byte currentState, byte newState)
{
    bool portStateChanged = false;
    if(currentState != newState)
    {
        portStateChanged = true;
    }
    return portStateChanged;
}

bool SensorsBuffer::getInputState(QString plateName, unsigned int portNumber, unsigned int inputNumber) const
{
    try
    {
        bool voltage = false;
        if(plateName == "portal")
        {
            voltage = this->checkPortalSensorState(portNumber, inputNumber);
        }
        else
        {
            if(plateName == "u1")
            {
                voltage = this->checkU1SensorState(portNumber, inputNumber);
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
    catch(std::runtime_error e)
    {
        qDebug() << "getInputState error: " << e.what();
        throw;
    }
    catch(std::invalid_argument e)
    {
        qDebug() << "getInputState error: " << e.what();
        throw;
    }
}

bool SensorsBuffer::checkPortalSensorState(unsigned int portNumber, unsigned int inputNumber) const
{
    try
    {
        bool voltage;
        switch(portNumber) {
        case 0:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[0]);
            break;
        }
        case 1:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[1]);
            break;
        }
        case 2:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[2]);
            break;
        }
        case 3:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[3]);
            break;
        }
        case 4:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[4]);
            break;
        }
        case 5:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[5]);
            break;
        }
        case 6:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[6]);
            break;
        }
        case 7:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[7]);
            break;
        }
        default:
            throw std::invalid_argument("invalid port number " + std::to_string(portNumber));
            break;
        }
        return voltage;
    }
    catch(std::runtime_error e)
    {
        qDebug() << "checkPortalSensorState error:" << e.what();
        throw;
    }
    catch(std::invalid_argument e)
    {
        qDebug() << "checkPortalSensorState error:" << e.what();
        throw;
    }
}

bool SensorsBuffer::checkU1SensorState(unsigned int portNumber, unsigned int inputNumber) const
{
    try
    {
        bool voltage;

        switch(portNumber) {
        case 0:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[8]);
            break;
        }
        case 1:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[9]);
            break;
        }
        case 2:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[10]);
            break;
        }
        case 3:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[11]);
            break;
        }
        case 4:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[12]);
            break;
        }
        case 5:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[13]);
            break;
        }
        case 6:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[14]);
            break;
        }
        case 7:
        {
            voltage = this->standardInputStateCheck(inputNumber, m_buffer[15]);
            break;
        }
        default:
            throw std::invalid_argument("invalid port number " + std::to_string(portNumber));
            break;
        }
        return voltage;
    }
    catch(std::runtime_error e)
    {
        qDebug() << "checkU1SensorState error:" << e.what();
        throw;
    }
    catch(std::invalid_argument e)
    {
        qDebug() << "checkU1SensorState error:" << e.what();
        throw;
    }
}
