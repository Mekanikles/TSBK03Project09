#include "point.h"

#include "stdlib.h"
#include "stdio.h"

#include "primitives.h"
#include "spring.h"

Point::Point(const Vector3& pos, double mass):
    pos(pos), old_pos(pos), mass(mass), velocity(Vector3(0,0,0)), impulse(Vector3(0,0,0)),displacement(Vector3(0,0,0)), locked(false), old_deltaT(1)
{
    
}

Point::Point():
    pos(Vector3(0,0,0)), old_pos(pos), mass(1.0), velocity(Vector3(0,0,0)), impulse(Vector3(0,0,0)), displacement(Vector3(0,0,0)), locked(false), old_deltaT(1)
{
    
}

Vector3 Point::getPos()
{
    return this->pos;
}

// Set new position
void Point::setPos(const Vector3& new_pos)
{
    this->pos = new_pos;
}

// Set new and old position explicitly, use this to set velocity
void Point::setPos(const Vector3& new_pos, const Vector3& old_pos)
{
    this->pos = new_pos;
    this->old_pos = old_pos;
}

// Add a force to the point
void Point::addForce(Vector3 force)
{
   this->force += force;
}

// Move a point, does not apply to locked points
void Point::displace(Vector3 d)
{
    if (!this->locked)
    {
        this->pos += d;
    }
}

// Perform verlet integration step
void Point::doVerletStep(double deltaT)
{
    // Calculate velocity
    Vector3 temp = this->pos;
   
    if (!this->locked)
    {
        // Simulate an energy loss of 20% per second
        double f = 0.2 * deltaT;
        this->pos = this->pos*(2-f) - this->old_pos*(1-f) + this->force/this->mass * deltaT * deltaT;
    }
    
    this->old_pos = temp;
}

// Apply accumulated force
void Point::applyForce(double deltaT)
{
    doVerletStep(deltaT);
    this->force = Vector3(0, 0, 0);
}

Vector3 Point::getForce()
{
    return this->impulse;
}

Vector3 Point::getVelocity()
{   
    return this->pos - this->old_pos;
}

double Point::getMass()
{
    return this->mass;
}

// Lock point, prevent it from moving due to displacements
void Point::lock(bool set)
{
    this->locked = set;
}

bool Point::isLocked()
{
    return this->locked;
}
