#include "switchon.h"

SwitchOn::SwitchOn(DevicesManager *_devicesManager, std::string _deviceName, std::string _parametrs) :
    devicesManager(_devicesManager), deviceName(_deviceName), parametrs(_parametrs)
{

}

SwitchOn::~SwitchOn()
{

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

void SwitchOn::draw(OGLWidget *w) const
{
    glPointSize(5.0f);
    w->qglColor(Qt::red);
    w->drawPoint(w->getCurrentPoint());
}

std::string SwitchOn::getName() const
{
    return name;
}

size_t SwitchOn::getId() const
{
    return id;
}

QStringList SwitchOn::getArguments() const
{
    QStringList arguments =
    {
        QString::fromStdString(deviceName),
        QString::fromStdString(parametrs)
    };
    return arguments;
}

QString SwitchOn::getArgumentsString() const
{
    QString qArgumentsString = QString::fromStdString(deviceName) + ", " + QString::fromStdString(parametrs);
    return qArgumentsString;
}

QColor SwitchOn::getColor() const
{
    return color;
}
