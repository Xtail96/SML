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
    try
    {
        Device &device = machineTool->getDevicesManager()->findDevice(deviceName);
        //toDo Преобразования строки в 2 байта
        byte_array data = machineTool->getDevicesManager()->getSwitchDeviceData(device, true);
        return data;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
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
