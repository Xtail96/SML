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

    Vector(int _x = 0, int _y = 0, int _z = 0, int _a = 0, int _b = 0) : x(_x), y(_y), z(_z), a(_a), b(_b) {}
};

#endif // VECTOR_H
