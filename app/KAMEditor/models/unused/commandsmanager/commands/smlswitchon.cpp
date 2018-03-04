#include "smlswitchon.h"

SMLSwitchOn::SMLSwitchOn(DevicesManager *_devicesManager, QString _deviceName, QString _parametrs) :
    devicesManager(_devicesManager), deviceName(_deviceName), parametrs(_parametrs)
{

}

SMLSwitchOn::~SMLSwitchOn()
{

}

byte_array SMLSwitchOn::getDataForMachineTool() const
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

void SMLSwitchOn::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        glPointSize(5.0f);
        w->qglColor(Qt::red);
        w->drawPoint(w->getCurrentPoint());
    }
}

QString SMLSwitchOn::getName() const
{
    return name;
}

size_t SMLSwitchOn::getId() const
{
    return id;
}

QStringList SMLSwitchOn::getArguments() const
{
    QStringList arguments =
    {
        deviceName,
        parametrs
    };
    return arguments;
}

void SMLSwitchOn::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 2)
    {
        deviceName = arguments[0];
        parametrs = arguments[1];
    }
}

QString SMLSwitchOn::getArgumentsString() const
{
    QString qArgumentsString = deviceName + ", " + parametrs;
    return qArgumentsString;
}

QColor SMLSwitchOn::getColor() const
{
    return color;
}

bool SMLSwitchOn::isArgumentsCorrect() const
{
    bool isCorrect = true;

    size_t tmp;
    tmp = parametrs.toUInt(&isCorrect);

    return isCorrect;
}
