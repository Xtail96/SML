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
    byte_array data;
    try
    {
        Device &device = machineTool->getDevicesManager()->findDevice(deviceName);
        //toDo Преобразования строки в 2 байта
        data = machineTool->getDevicesManager()->getSwitchDeviceData(device, true);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return data;
}

void SwitchOn::draw(OGLWidget *w, Point3D sourcePoint) const
{
    w->drawCylinder(0.1, 0.2, sourcePoint);
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

void OGLWidget::drawCylinder(double radius, double height, Point3D src)
{
    double angleIncrement = 0.01;

    double x, y;

    glBegin(GL_LINE_STRIP);

    for (double theta = 0; theta < 360; theta += angleIncrement)
    {
        x = radius * cos(theta) + src.x;
        y = radius * sin(theta) + src.y;

        glVertex2f(x, y);
    }

    glEnd();
}
