#include "axis.h"
Axis::Axis(std::string _name,
           double _step,
           double _length,
           bool _invertDirection,
           double _jerk,
           double _acceleration,
           double _velocity,
           int _channel,
           double _basingVelocity) :
    name(_name),
    step(_step),
    length(_length),
    invertDirection(_invertDirection),
    jerk(_jerk),
    acceleration(_acceleration),
    velocity(_velocity),
    channel(_channel),
    basingVelocity(_basingVelocity)
{

}

Axis::Axis(std::string _name, SettingsManager *sm) :
    name(_name)
{
    if(sm == nullptr)
    {
        qDebug() << QString("new SettingsManager instance in axis ") + QString::fromStdString(name);
        sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
    else
    {
        setup(sm);
    }
}
double Axis::getStep() const
{
    return step;
}

void Axis::setStep(double value)
{
    step = value;
}

double Axis::getLength() const
{
    return length;
}

void Axis::setLength(double value)
{
    length = value;
}

bool Axis::getInvertDirection() const
{
    return invertDirection;
}

void Axis::setInvertDirection(bool value)
{
    invertDirection = value;
}

double Axis::getJerk() const
{
    return jerk;
}

void Axis::setJerk(double value)
{
    jerk = value;
}

double Axis::getAcceleration() const
{
    return acceleration;
}

void Axis::setAcceleration(double value)
{
    acceleration = value;
}

double Axis::getVelocity() const
{
    return velocity;
}

void Axis::setVelocity(double value)
{
    velocity = value;
}

int Axis::getChannel() const
{
    return channel;
}

void Axis::setChannel(int value)
{
    channel = value;
}

double Axis::getBasingVelocity() const
{
    return basingVelocity;
}

void Axis::setBasingVelocity(double value)
{
    basingVelocity = value;
}

std::string Axis::getName() const
{
    return name;
}

void Axis::setName(const std::string &value)
{
    name = value;
}

void Axis::setup(SettingsManager* sm)
{
    try
    {
        QString qAxisName = QString("Axis") + QString::fromStdString(name);

        QVariant qAcceleration = sm->get(qAxisName, "Acceleration");
        acceleration = qAcceleration.toDouble();

        QVariant qBazaSearchSpeed = sm->get(qAxisName, "BazaSearchSpeed");
        basingVelocity = qBazaSearchSpeed.toDouble();

        QVariant qChannel = sm->get(qAxisName, "Channel");
        channel = qChannel.toInt();

        QVariant qJerk = sm->get(qAxisName, "Jerk");
        jerk = qJerk.toDouble();

        QVariant qVelocity = sm->get(qAxisName, "Speed");
        velocity = qVelocity.toDouble();

        QVariant qLength = sm->get("TableSize", QString("Size" + QString::fromStdString(name)));
        length = qLength.toDouble();

        QVariant qStep = sm->get(qAxisName, "Step");
        step = qStep.toDouble();

        QVariant qInvertDirection = sm->get(qAxisName, "Invert");
        invertDirection = qInvertDirection.toBool();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, QString("Ошибка настройки оси ") + QString::fromStdString(name), e.what()).exec();
    }
}
