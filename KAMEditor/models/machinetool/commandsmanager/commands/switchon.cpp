#include "switchon.h"

SwitchOn::SwitchOn(MachineTool *_machineTool, std::vector<std::string> _arguments) :
    machineTool(_machineTool), arguments(_arguments)
{

}

SwitchOn::~SwitchOn()
{
    //delete machineTool;
}

void SwitchOn::send() const
{
    try
    {
        Device &device = machineTool->getDevicesManager()->findDevice(arguments[0]);
        byte_array data = machineTool->getDevicesManager()->getSwitchDeviceData(device, true);
#ifdef Q_OS_WIN
        try
        {
            u1Manager->getU1()->sendData(data);
        }
        catch(std::runtime_error e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
        }
#endif
        device.setCurrentState(device.getActiveState());
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
    std::string argumentsString = "";
    for(auto argument : arguments)
    {
        argumentsString += argument + ", ";
    }
    return QString::fromStdString(argumentsString);
}
