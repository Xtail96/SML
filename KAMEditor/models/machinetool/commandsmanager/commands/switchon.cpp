#include "switchon.h"

QColor SwitchOn::getColor() const
{
    return color;
}

SwitchOn::SwitchOn(MachineTool *_machineTool, std::string _deviceName, std::string _parametrs) :
    machineTool(_machineTool), deviceName(_deviceName), parametrs(_parametrs)
{

}

SwitchOn::~SwitchOn()
{
    //delete machineTool;
}

byte_array SwitchOn::getDataForMachineTool() const
{
    byte_array data;
    try
    {
        Device &device = machineTool->getDevicesManager()->findDevice(deviceName);
        //toDo Преобразования строки в 2 байта
        data = machineTool->getDevicesManager()->getSwitchDeviceData(device, true);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return data;
}

void SwitchOn::draw(OGLWidget *w) const
{

}

std::string SwitchOn::getName() const
{
    return name;
}

size_t SwitchOn::getId() const
{
    return id;
}

QString SwitchOn::getArguments() const
{
    std::string argumentsString = deviceName + ", " + parametrs;
    return QString::fromStdString(argumentsString);
}
