#include "smlswitchoff.h"

SMLSwitchOff::SMLSwitchOff(DevicesManager *_devicesManager, QString _deviceName, QString _parametrs) :
    devicesManager(_devicesManager),
    deviceName(_deviceName),
    parametrs(_parametrs)
{

}

SMLSwitchOff::~SMLSwitchOff()
{

}

byte_array SMLSwitchOff::getDataForMachineTool() const
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

void SMLSwitchOff::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        glPointSize(5.0f);
        w->qglColor(Qt::green);
        w->drawPoint(w->getCurrentPoint());
    }
}

QString SMLSwitchOff::getName() const
{
    return name;
}

size_t SMLSwitchOff::getId() const
{
    return id;
}

QStringList SMLSwitchOff::getArguments() const
{
    QStringList arguments =
    {
        deviceName,
        parametrs
    };
    return arguments;
}

void SMLSwitchOff::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 2)
    {
        deviceName = arguments[0];
        parametrs = arguments[1];
    }
}

QString SMLSwitchOff::getArgumentsString() const
{
    QString qArgumentsString = deviceName + ", " + parametrs;
    return qArgumentsString;
}

QColor SMLSwitchOff::getColor() const
{
    return color;
}

bool SMLSwitchOff::isArgumentsCorrect() const
{
    return true;
}
