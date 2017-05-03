#ifndef VECTOR_H
#define VECTOR_H
#include <string>

struct VectorDouble
{
    double x;
    double y;
    double z;

    double a;
    double b;

    VectorDouble(double _x = 0, double _y = 0, double _z = 0, double _a = 0, double _b = 0) : x(_x), y(_y), z(_z), a(_a), b(_b) {}
};

/// Настройки KFlop
struct AxisKFlopSettings
{
    double jerk;
    double acceleration;
    double velocity;
    int channel;
    double basingVelocity;
    AxisKFlopSettings(double _jerk = 0, double _acceleration = 0, double _velocity = 0, int _channel = 0, double _basingVelocity = 0)
        : jerk(_jerk), acceleration(_acceleration), velocity(_velocity), channel(_channel), basingVelocity(_basingVelocity){}
};

struct Axis
{
    std::string name;
    double step;
    double length;
    bool invertDirection;
    double jerk;
    double acceleration;
    double velocity;
    int channel;
    double basingVelocity;

    Axis(std::string id, double _step = 0, double _length = 1, bool invert = 0, double _jerk = 0, double _acceleration = 0, double _velocity = 0, int _channel = 0, double _basingVelocity = 0) :
        name(id),
        step(_step),
        length(_length),
        invertDirection(invert),
        jerk(_jerk),
        acceleration(_acceleration),
        velocity(_velocity),
        channel(_channel),
        basingVelocity(_basingVelocity){}
};


#endif // VECTOR_H
