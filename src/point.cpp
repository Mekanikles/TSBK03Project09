#include "point.h"

#include  "stdlib.h"

#include "primitives.h"
#include "spring.h"

Point::Point(const Vector3& pos, double mass):
    pos(pos), old_pos(pos), mass(mass), velocity(Vector3(0,0,0)), impulse(Vector3(0,0,0)), locked(false), old_deltaT(1)
{
    
}

Point::Point():
    pos(Vector3(0,0,0)), old_pos(pos), mass(1.0), velocity(Vector3(0,0,0)), impulse(Vector3(0,0,0)), locked(false), old_deltaT(1)
{
    
}

Vector3 Point::getPos()
{
    return this->pos;
}

void Point::setPos(const Vector3& new_pos)
{
    this->pos = new_pos;
    this->old_pos = new_pos;
}

void Point::setPos(const Vector3& new_pos, const Vector3& old_pos)
{
    this->pos = new_pos;
    this->old_pos = old_pos;
}

void Point::addImpulse(Vector3 impulse)
{
   this->impulse += impulse;
}

void Point::doVerletStep(double deltaT)
{
    // Calculate velocity
    Vector3 temp = this->pos;
    //this->velocity = (this->pos - this->old_pos) / deltaT;
    this->velocity = this->velocity - this->velocity * (0.5 * deltaT);
    this->velocity += this->impulse/this->mass * deltaT;
    
    // Verlet integration
    this->pos += this->velocity * deltaT;
    this->pos += (this->impulse/this->mass) * deltaT * deltaT;
    
    this->old_pos = temp;
    this->old_deltaT = deltaT;
}

void Point::applyForce(double deltaT)
{
    doVerletStep(deltaT);
    this->impulse = Vector3(0, 0, 0);
}

Vector3 Point::getImpulse()
{
    return this->impulse;
}

Vector3 Point::getVelocity()
{   
    return this->velocity; //this->pos - this->old_pos;
}

void Point::setVelocity(const Vector3& vel)
{   
    this->velocity = vel; //this->pos - this->old_pos;
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

void Point::addNeighbor(Point* p, double elasticity)
{
    Spring* s = new Spring(this, p, elasticity);
    this->springs.addFirst(s);
}

void Point::addSpringForces()
{
    for (Node<Spring*>* s = this->springs.getFirst(); s != NULL; s = s->next)
    {
        s->item->addForces();
    }
}

void Point::setupSprings()
{
    for (Node<Spring*>* s = this->springs.getFirst(); s != NULL; s = s->next)
    {
        s->item->calcInertialLength();
    }
}

LinkedList<Spring*>* Point::getSpringList()
{
    return &this->springs;
}
