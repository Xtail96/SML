#include "switchon.h"

SwitchOn::SwitchOn(DevicesManager *_devicesManager, QString _deviceName, QString _parametrs) :
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
        //Device &device = devicesManager->findDevice(deviceName);
        //toDo Преобразования строки в 2 байта
        //data = devicesManager->getSwitchDeviceData(device, true);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return data;
}

void SwitchOn::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        glPointSize(5.0f);
        w->qglColor(Qt::red);
        w->drawPoint(w->getCurrentPoint());
    }
}

QString SwitchOn::getName() const
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
        deviceName,
        parametrs
    };
    return arguments;
}

QString SwitchOn::getArgumentsString() const
{
    QString qArgumentsString = deviceName + ", " + parametrs;
    return qArgumentsString;
}

QColor SwitchOn::getColor() const
{
    return color;
}

bool SwitchOn::isArgumentsCorrect() const
{
    bool isCorrect = true;

    size_t tmp;
    tmp = parametrs.toUInt(&isCorrect);

    return isCorrect;
}
