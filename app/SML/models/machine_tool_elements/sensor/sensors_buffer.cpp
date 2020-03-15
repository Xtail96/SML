#include "sensors_buffer.h"

SensorsBuffer::SensorsBuffer(size_t bufferSize)
{
    this->resetBuffer(bufferSize);
}

void SensorsBuffer::resetBuffer(size_t size)
{
    m_buffer.clear();
    for(size_t i = 0; i < size; i++)
    {
        m_buffer.push_back(0x00);
    }
}

void SensorsBuffer::updateBuffer(byte_array value)
{
    if(value.size() == m_buffer.size())
    {
        m_buffer = value;
    }
    else
    {
        QString message = QStringLiteral("invalid buffer size. ") +
                QString::number(m_buffer.size()) +
                " != " + QString::number(value.size());
        throw SynchronizeStateException(message);
    }
}

bool SensorsBuffer::standardInputStateCheck(size_t inputNumber, byte portState) const
{
    if (inputNumber > 7)
    {
        QString message =
                QStringLiteral("Invalid input number. ") +
                QString::number(inputNumber) +
                QStringLiteral(" > 7");

        throw SynchronizeStateException(message);
    }

    bool voltage = true;

    byte tmp = portState;
    // сдвигаем все биты влево, чтобы исключить все биты слева, а нужный бит стоял в старшем разряде
    tmp = static_cast<byte>(tmp << (7 - inputNumber));

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
            QString message =
                    QStringLiteral("an error has occured during analyze sensor ") +
                    QString::number(inputNumber) +
                    QStringLiteral(" ") +
                    QString(portState);

            throw SynchronizeStateException(message);
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

bool SensorsBuffer::getInputState(QString plateName, size_t portNumber, size_t inputNumber) const
{
    if (portNumber > static_cast<size_t>(m_buffer.size()))
    {
        QString message =
                QStringLiteral("Invalid port.") +
                QStringLiteral(" ") +
                QString::number(portNumber) +
                QStringLiteral(" >= ") +
                QString::number(m_buffer.size());

        throw SynchronizeStateException(message);
    }

    if(inputNumber > 7)
    {
        QString message =
                QStringLiteral("Invalid input.") +
                QStringLiteral(" ") +
                QString::number(inputNumber) +
                QStringLiteral(" > 7");

        throw SynchronizeStateException(message);
    }

    try
    {
        bool voltage = false;
        if(plateName == "u1")
        {
            voltage = this->checkU1SensorState(portNumber, inputNumber);
        }
        else
        {
            if(plateName == "u2")
            {
                voltage = this->checkU2SensorState(portNumber, inputNumber);
            }
            else
            {
                QString message =
                        QStringLiteral("Unknown plateName = ") +
                        plateName;
                throw SynchronizeStateException(message);
            }
        }
        return voltage;
    }
    catch(SynchronizeStateException e)
    {
        qDebug() << QStringLiteral("SensorsBuffer::getInputState:") << e.message();
        throw;
    }
}

bool SensorsBuffer::checkU1SensorState(size_t portNumber, size_t inputNumber) const
{
    if (portNumber > 7)
    {
        QString message =
                QStringLiteral("invalid port number. ") +
                QString::number(portNumber) +
                QStringLiteral(" > 7");
        throw SynchronizeStateException(message);
    }

    if (inputNumber > 7)
    {
        QString message =
                QStringLiteral("invalid input number. ") +
                QString::number(inputNumber) +
                QStringLiteral(" > 7");
        throw SynchronizeStateException(message);
    }

    try
    {
        bool voltage = false;
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
            break;
        }
        return voltage;
    }
    catch(SynchronizeStateException e)
    {
        qDebug() << "SensorsBuffer::checkU1SensorState:" << e.message();
        throw;
    }
}

bool SensorsBuffer::checkU2SensorState(size_t portNumber, size_t inputNumber) const
{
    if (portNumber > 7)
    {
        QString message =
                QStringLiteral("invalid port number. ") +
                QString::number(portNumber) +
                QStringLiteral(" > 7");
        throw SynchronizeStateException(message);
    }

    if (inputNumber > 7)
    {
        QString message =
                QStringLiteral("invalid input number. ") +
                QString::number(inputNumber) +
                QStringLiteral(" > 7");
        throw SynchronizeStateException(message);
    }

    try
    {
        bool voltage = false;

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
            break;
        }
        return voltage;
    }
    catch(SynchronizeStateException e)
    {
        qDebug() << "SensorsBuffer::checkU2SensorState:" << e.message();
        throw;
    }
}
