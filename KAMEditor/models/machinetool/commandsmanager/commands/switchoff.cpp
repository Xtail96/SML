#include "switchoff.h"

SwitchOff::SwitchOff(MachineTool *_machineTool, std::string _deviceName, std::string _parametrs) :
    machineTool(_machineTool),
    deviceName(_deviceName),
    parametrs(_parametrs)
{

}

SwitchOff::~SwitchOff()
{

}

byte_array SwitchOff::getDataForMachineTool() const
{
    byte_array data;
    try
    {
        Device &device = machineTool->getDevicesManager()->findDevice(deviceName);
        //toDo Преобразования строки в 2 байта
        data = machineTool->getDevicesManager()->getSwitchDeviceData(device, false);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return data;
}

void SwitchOff::draw(OGLWidget *w, SourcePoint sourcePoint) const
{

}

std::string SwitchOff::getName() const
{
    return name;
}

size_t SwitchOff::getId() const
{
    return id;
}

QString SwitchOff::getArguments() const
{
    std::string argumentsString = deviceName + ", " + parametrs;
    return QString::fromStdString(argumentsString);
}

QColor SwitchOff::getColor() const
{
    return color;
}
