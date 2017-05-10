#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <map>


struct VectorDouble
{
    double x;
    double y;
    double z;

    double a;
    double b;

    VectorDouble(double _x = 0, double _y = 0, double _z = 0, double _a = 0, double _b = 0) : x(_x), y(_y), z(_z), a(_a), b(_b) {}
};

struct
{
    std::map<unsigned int, std::string> axisNames =
    {
        {0, "X"},
        {1, "Y"},
        {2, "Z"},
        {3, "A"},
        {4, "B"},
        {5, "C"},
        {6, "D"},
        {7, "E"},
        {8, "F"},
        {9, "G"},
        {10, "H"},
    };

    std::string getNameByValue(const unsigned int &value)
    {
        if(value < axisNames.size())
        {
            return axisNames[value];
        }
        else
        {
            return "undefined";
        }
    }
    int getValueByName(const std::string &s) const
    {
        int axisNumber = -1;
        for(auto it : axisNames)
        {
            if(it.second == s)
            {
                axisNumber =  it.first;
                break;
            }
        }
        return axisNumber;
    }
} axisNames;

/// Настройки KFlop
//struct AxisKFlopSettings
//{
//    double jerk;
//    double acceleration;
//    double velocity;
//    int channel;
//    double basingVelocity;
//    AxisKFlopSettings(double _jerk = 0, double _acceleration = 0, double _velocity = 0, int _channel = 0, double _basingVelocity = 0)
//        : jerk(_jerk), acceleration(_acceleration), velocity(_velocity), channel(_channel), basingVelocity(_basingVelocity){}
//};
#endif // VECTOR_H
