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

void SwitchOff::draw(OGLWidget *w) const
{
    glPointSize(5.0f);
    w->qglColor(Qt::green);
    w->drawPoint(w->getCurrentPoint());
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

QString SwitchOff::getArgumentsString() const
{
    QString qArgumentsString = QString::fromStdString(deviceName) + ", " + QString::fromStdString(parametrs);
    return qArgumentsString;
}

QColor SwitchOff::getColor() const
{
    return color;
}
