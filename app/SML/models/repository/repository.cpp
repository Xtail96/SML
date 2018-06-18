#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_settingsManager(new SettingsManager()),
    m_u1Connection(new Connection(this)),
    m_u2Connection(new Connection(this))
{
    loadSettigs();
}

void Repository::loadSettigs()
{
    loadServerSettings();
    loadServerSettings();
    loadDevicesSettings();
    loadAxisesSettings();
}

void Repository::loadServerSettings()
{
    try
    {
        m_port = m_settingsManager->get("ServerSettings", "ServerPort").toUInt();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации порта сервера") + QString(e.what())).exec();
    }
}

void Repository::loadSensorsSettings()
{
    try
    {
        unsigned int sensorsCount = QVariant(m_settingsManager->get("MachineToolInformation", "SensorsCount")).toUInt();

        std::vector<QString> sensorsCodes;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            QString sensorString = QString("Sensor") + QString::number(i);
            sensorsCodes.push_back(sensorString);
        }

        for(auto code : sensorsCodes)
        {
            QString name  = QVariant(m_settingsManager->get(code, "Name")).toString();
            QString label = QVariant(m_settingsManager->get(code, "Label")).toString();
            size_t portNumber = QVariant(m_settingsManager->get(code, "PortNumber")).toUInt();
            size_t inputNumber = QVariant(m_settingsManager->get(code, "InputNumber")).toUInt();
            QString boardName = QVariant(m_settingsManager->get(code, "BoardName")).toString();
            bool activeState = QVariant(m_settingsManager->get(code, "ActiveState")).toBool();
            QColor color = QColor(QVariant(m_settingsManager->get(code, "Color")).toString());

            Sensor* sensor = new Sensor(name,
                                        label,
                                        portNumber,
                                        inputNumber,
                                        boardName,
                                        activeState,
                                        color,
                                        this);
            m_sensors.push_back(QSharedPointer<Sensor>(sensor));
        }

        size_t bufferSize = QVariant(m_settingsManager->get("MachineToolInformation", "SensorsBufferSize")).toUInt();
        m_sensorsBuffer.resetBuffer(bufferSize);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера датчиков", e.what()).exec();
    }
}

void Repository::loadDevicesSettings()
{
    try
    {
        unsigned int spindelsCount = QVariant(m_settingsManager->get("MachineToolInformation", "SpindelsCount")).toUInt();
        unsigned int supportDevicesCount = QVariant(m_settingsManager->get("MachineToolInformation", "SupportDevicesCount")).toUInt();

        for(unsigned int i = 0; i < spindelsCount; i++)
        {
            QString name = QString("Spindel") + QString::number(i);
            QString label = QVariant(m_settingsManager->get(name, "Label")).toString();
            QString index = QVariant(m_settingsManager->get(name, "Index")).toString();
            bool activeState = QVariant(m_settingsManager->get(name, "ActiveState")).toBool();
            int mask = QVariant(m_settingsManager->get(name, "Mask")).toUInt();
            size_t upperBound = QVariant(m_settingsManager->get(name, "UpperBound")).toULongLong();
            size_t lowerBound = QVariant(m_settingsManager->get(name, "LowerBound")).toULongLong();


            Spindel* spindel = new Spindel(name,
                                           label,
                                           index,
                                           activeState,
                                           mask,
                                           lowerBound,
                                           upperBound,
                                           this);
            m_spindels.push_back(QSharedPointer<Spindel> (spindel));
        }

        for(unsigned int i = 0; i < supportDevicesCount; i++)
        {
            QString name = QString("SupportDevice") + QString::number(i);
            QString label = QVariant(m_settingsManager->get(name, "Label")).toString();
            QString index = QVariant(m_settingsManager->get(name, "Index")).toString();
            bool activeState = QVariant(m_settingsManager->get(name, "ActiveState")).toBool();
            int mask = QVariant(m_settingsManager->get(name, "Mask")).toUInt();


            SupportDevice* device = new SupportDevice(name,
                                                      label,
                                                      index,
                                                      activeState,
                                                      mask,
                                                      this);
            m_supportDevices.push_back(QSharedPointer<SupportDevice> (device));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера устройств", e.what()).exec();
    }
}

void Repository::loadAxisesSettings()
{
    try
    {
         size_t axisesCount = m_settingsManager->get("MachineToolInformation", "AxisesCount").toUInt();
         for(size_t i = 0; i < axisesCount; i++)
         {
             QString name = SML_AXISES_NAMES.getNameByKey(i);

             QString fullAxisName = QString("Axis") + name;

             double length = m_settingsManager->get("TableSize", QString("Size" + name)).toDouble();
             double step = m_settingsManager->get(fullAxisName, "Step").toDouble();
             bool invertDirection = m_settingsManager->get(fullAxisName, "Invert").toBool();
             double bazaSearchSpeed = m_settingsManager->get(fullAxisName, "BazaSearchSpeed").toDouble();

             QSharedPointer<Axis> axis = QSharedPointer<Axis>(new Axis(name, length, step, invertDirection, bazaSearchSpeed));
             m_axises.push_back(axis);
         }
         m_zeroCoordinates = Point(m_axises.size());
         m_parkCoordinates = Point(m_axises.size());
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации менеджера осей!") + QString(e.what())).exec();
    }
}

void Repository::setU1Connected(bool connected)
{
    m_u1Connection->setConnected(connected);
}

void Repository::setU1Sensors(QList<QVariant> sensors)
{
    byte_array currentSensorsState;
    for(auto port : sensors)
    {
        currentSensorsState.push_back(port.toUInt());
    }

    m_sensorsBuffer.updateBuffer(currentSensorsState);
    for(auto sensor : m_sensors)
    {
        bool isVoltage = m_sensorsBuffer.getInputState(sensor->getBoardName(),
                                                       sensor->getPortNumber(),
                                                       sensor->getInputNumber());
        sensor->update(isVoltage);
    }
}

void Repository::setU1Devices(QList<QVariant> devices)
{
    byte_array currentDevicesState;
    for(auto device : devices)
    {
        currentDevicesState.push_back(device.toUInt());
    }

    for(size_t i = 0; i < currentDevicesState.size(); i++)
    {
        try
        {
            Device& device = findDevice(i);
            if(currentDevicesState[i] == 0x01)
            {
                device.updateCurrentState(device.getActiveState());
            }
            else
            {
                if(currentDevicesState[i] == 0x00)
                {
                    device.updateCurrentState(!device.getActiveState());
                }
            }
        }
        catch(std::invalid_argument e)
        {
            qDebug() << e.what() << i;
        }
    }

}

void Repository::setU1Error(int code)
{
    m_u1Connection->setLastError(code);
}

Device &Repository::findDevice(size_t index)
{
    for(auto device : m_spindels)
    {
        if(device->getIndex().toUInt() == index)
        {
            return *device;
        }
    }

    for(auto device : m_supportDevices)
    {
        if(device->getIndex().toUInt() == index)
        {
            return *device;
        }
    }

    std::string errorString = "device not found";
    throw std::invalid_argument(errorString);
}