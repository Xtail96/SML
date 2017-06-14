#include "axis.h"

Axis::Axis(std::string id, std::string _type, double _step, double _length, bool invert, double _jerk, double _acceleration, double _velocity, int _channel, double _basingVelocity) :
    name(id),
    type(_type),
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

std::string Axis::getType() const
{
    return type;
}

void Axis::setType(const std::string &value)
{
    type = value;
}

std::string Axis::getName() const
{
    return name;
}

void Axis::setName(const std::string &value)
{
    name = value;
}

void Axis::setup(const std::map<std::string, std::string> &settingsMap)
{
    if(settingsMap.size() != 0)
    {
        setupAxisAcceleration(name, settingsMap);
        setupAxisBazaSearchSpeed(name, settingsMap);
        setupAxisChannel(name, settingsMap);
        setupAxisInvertStatus(name, settingsMap);
        setupAxisJerk(name, settingsMap);
        setupAxisSpeed(name, settingsMap);
        setupAxisStep(name, settingsMap);
        setupAxisTableSize(name, settingsMap);
    }
}

std::string Axis::getSettingsElement(std::string key, std::map<std::string, std::string> allSettings)
{
    if(allSettings.find(key) != allSettings.end())
    {
        return allSettings[key];
    }
    else
    {
        return "0";
    }
}

void Axis::setupAxisAcceleration(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = name + "_Axis_acceleration";
    std::string axisAccelration = getSettingsElement(key, allSettings);
    acceleration = std::stod(axisAccelration);
}

void Axis::setupAxisBazaSearchSpeed(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = name +"_Axis_bazaSearchSpeed";
    std::string axisBazaSearchSpeed = getSettingsElement(key, allSettings);
    basingVelocity = std::stod(axisBazaSearchSpeed);
}

void Axis::setupAxisChannel(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = name + "_Axis_channel";
    std::string axisChannel = getSettingsElement(key, allSettings);
    channel = std::stod(axisChannel);
}

void Axis::setupAxisJerk(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = name + "_Axis_jerk";
    std::string axisJerk = getSettingsElement(key, allSettings);
    jerk = std::stod(axisJerk);
}

void Axis::setupAxisSpeed(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = name + "_Axis_speed";
    std::string axisSpeed = getSettingsElement(key, allSettings);
    velocity = std::stod(axisSpeed);
}

void Axis::setupAxisStep(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = "Mashin_Info_AltSteps" + name;
    std::string axisAltStep = getSettingsElement(key, allSettings);
    step = std::stod(axisAltStep);
}

void Axis::setupAxisInvertStatus(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = "Mashin_Info_Invert" + name;
    std::string axisInvertStatus = getSettingsElement(key, allSettings);
    int tmp = std::stoi(axisInvertStatus);
    if(tmp == 1)
    {
        invertDirection = true;
    }
    else
    {
        invertDirection = false;
    }
}

void Axis::setupAxisTableSize(const std::string &name, const std::map<std::string, std::string> &allSettings)
{
    std::string key = "Table_Size_Size" + name;
    std::string axisTableSize = getSettingsElement(key, allSettings);
    length = std::stod(axisTableSize);
}
