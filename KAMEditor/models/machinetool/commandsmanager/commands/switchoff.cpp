#include "switchoff.h"

SwitchOff::SwitchOff(DevicesManager *_devicesManager, QString _deviceName, QString _parametrs) :
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
        Device &device = devicesManager->findDevice(deviceName.toStdString());
        //toDo Преобразования строки в 2 байта
        data = devicesManager->getSwitchDeviceData(device, false);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return data;
}

void SwitchOff::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        glPointSize(5.0f);
        w->qglColor(Qt::green);
        w->drawPoint(w->getCurrentPoint());
    }
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
        deviceName,
        parametrs
    };
    return arguments;
}

QString SwitchOff::getArgumentsString() const
{
    QString qArgumentsString = deviceName + ", " + parametrs;
    return qArgumentsString;
}

QColor SwitchOff::getColor() const
{
    return color;
}

bool SwitchOff::isArgumentsCorrect() const
{
    return true;
}
