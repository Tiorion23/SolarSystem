#include "Vectorld2d.h"
#include <math.h>
#include <assert.h> // для assert()

Vectorld2d::Vectorld2d() {
    x = 0;
    y = 0;
}

Vectorld2d::Vectorld2d(long double ax, long double ay) {
    x = ax;
    y = ay;
}

bool operator==(const Vectorld2d& v1, const Vectorld2d& v2)
{
    if (v1.x == v2.x && v1.y == v2.y)
        return true;
    return false;
}

bool operator!=(const Vectorld2d& v1, const Vectorld2d& v2)
{
    if (v1.x == v2.x && v1.y == v2.y)
        return false;
    return true;
}

long double& Vectorld2d::operator[](int index)
{
    switch (index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        default:
            break;
    }        
}

Vectorld2d& Vectorld2d::operator= (const Vectorld2d& v) {
    if (this == &v)
        return *this;
    x = v.x;
    y = v.y;
    return *this;
}

Vectorld2d operator+ (const Vectorld2d& v1, const Vectorld2d& v2) {
    Vectorld2d result = Vectorld2d(v1.x + v2.x, v1.y + v2.y);
    return result;
}

Vectorld2d operator* (const Vectorld2d& v1, const int m) {
    Vectorld2d result = Vectorld2d(v1.x * m, v1.y * m);
    return result;
}

Vectorld2d operator* (const Vectorld2d& v1, const long double m) {
    Vectorld2d result = Vectorld2d(v1.x * m, v1.y * m);
    return result;
}

const long double Vectorld2d::length() {
    return sqrt(pow(x, 2) + pow(y, 2));
}