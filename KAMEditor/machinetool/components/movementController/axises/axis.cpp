#include "axis.h"
Axis::Axis(std::string id, double _step, double _length, bool invert, double _jerk, double _acceleration, double _velocity, int _channel, double _basingVelocity) :
    name(id),
    step(_step),
    length(_length),
    invertDirection(invert),
    jerk(_jerk),
    acceleration(_acceleration),
    velocity(_velocity),
    channel(_channel),
    basingVelocity(_basingVelocity)
{

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

void Axis::setup(const SettingsManager &settings)
{
    QString qAxisName = QString(QString::fromStdString(name) + " Axis");

    QVariant qAcceleration = settings.get(qAxisName, "acceleration");
    acceleration = qAcceleration.toDouble();

    QVariant qBazaSearchSpeed = settings.get(qAxisName, "bazaSearchSpeed");
    basingVelocity = qBazaSearchSpeed.toDouble();

    QVariant qChannel = settings.get(qAxisName, "channel");
    channel = qChannel.toInt();

    QVariant qJerk = settings.get(qAxisName, "jerk");
    jerk = qJerk.toDouble();

    QVariant qVelocity = settings.get(qAxisName, "speed");
    velocity = qVelocity.toDouble();

    QVariant qLength = settings.get("Table_Size", QString("Size" + QString::fromStdString(name)));
    length = qLength.toDouble();

    QVariant qStep = settings.get("Mashin_Info", QString("AltSteps" + QString::fromStdString(name)));
    step = qStep.toDouble();

    QVariant qInvertDirection = settings.get("Mashin_Info", QString("Invert" + QString::fromStdString(name)));
    invertDirection = qInvertDirection.toBool();
}
