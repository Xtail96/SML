#include "switchon.h"

QColor SwitchOn::getColor() const
{
    return color;
}

SwitchOn::SwitchOn(DevicesManager *_devicesManager, std::string _deviceName, std::string _parametrs) :
    devicesManager(_devicesManager), deviceName(_deviceName), parametrs(_parametrs)
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
        Device &device = devicesManager->findDevice(deviceName);
        //toDo Преобразования строки в 2 байта
        data = devicesManager->getSwitchDeviceData(device, true);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return data;
}

void SwitchOn::draw(OGLWidget *w, Point3D sourcePoint) const
{
    //glColor3f(1, 0, 0);
    w->drawPoint(sourcePoint, "Включение");
}

Point3D SwitchOn::returnDestinationPoint(Point3D sourcePoint) const
{
    return sourcePoint;
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
