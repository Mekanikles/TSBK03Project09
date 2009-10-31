#include "point.h"

#include "primitives.h"

Point::Point(const Vector3& pos, double mass):
    pos(pos), mass(mass)
{
    
}

Point::Point():
    pos(Vector3(0,0,0)), mass(1.0)
{
    
}

Vector3 Point::getPos()
{
    return this->pos;
}
