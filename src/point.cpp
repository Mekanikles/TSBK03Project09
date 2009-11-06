#include "point.h"

#include "primitives.h"

Point::Point(const Vector3& pos, double mass):
    pos(pos), old_pos(pos), mass(mass), force(Vector3()), locked(false)
{
    
}

Point::Point():
    pos(Vector3(0,0,0)), old_pos(pos), mass(1.0), force(Vector3()), locked(false)
{
    
}

Vector3 Point::getPos()
{
    return this->pos;
}

void Point::setPos(const Vector3& pos)
{
    this->pos = pos;
    this->old_pos = pos;
}

void Point::addForce(Vector3 force)
{
    this->force += force;
}

void Point::applyForce(double deltaT)
{
    // Verlet integration
    Vector3 temp = this->pos;
    this->pos += this->getVelocity() * 0.99 + (this->force/this->mass) * deltaT * deltaT;
    this->old_pos = temp;
    
    this->force = Vector3(0, 0, 0);
}

Vector3 Point::getForce()
{
    return this->force;
}

Vector3 Point::getVelocity()
{   
    return this->pos - this->old_pos;
}

double Point::getMass()
{
    return this->mass;
}

void Point::Lock(bool set)
{
    this->locked = set;
}

bool Point::isLocked()
{
    return this->locked;
}
