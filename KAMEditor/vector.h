#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:

    double x;
    double y;
    double z;

    double a;
    double b;

    Vector(double _x = 0, double _y = 0, double _z = 0, double _a = 0, double _b = 0) : x(_x), y(_y), z(_z), a(_a), b(_b) {}
};

#endif // VECTOR_H
