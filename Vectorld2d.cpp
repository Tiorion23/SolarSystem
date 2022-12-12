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

Vectorld2d::Vectorld2d(const Vectorld2d& v) {
    this->x = v.x;
    this->y = v.y;
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

const long double Vectorld2d::length() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Vectorld2d::mirror() {
    x = -x;
    y = -y;
}