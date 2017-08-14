#include "switchoff.h"

SwitchOff::SwitchOff(DevicesManager *_devicesManager, std::string _deviceName, std::string _parametrs) :
    devicesManager(_devicesManager),
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
        Device &device = devicesManager->findDevice(deviceName);
        //toDo Преобразования строки в 2 байта
        data = devicesManager->getSwitchDeviceData(device, false);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return data;
}

void SwitchOff::draw(OGLWidget *w, Point3D sourcePoint) const
{
    glPointSize(5.0f);
    w->qglColor(Qt::green);
    w->drawPoint(sourcePoint);
}

Point3D SwitchOff::returnDestinationPoint(Point3D sourcePoint) const
{
    return sourcePoint;
}

std::string SwitchOff::getName() const
{
    return name;
}

size_t SwitchOff::getId() const
{
    return id;
}

QStringList SwitchOff::getArguments() const
{
    QStringList arguments =
    {
        QString::fromStdString(deviceName),
        QString::fromStdString(parametrs)
    };
    return arguments;
}

QColor SwitchOff::getColor() const
{
    return color;
}
