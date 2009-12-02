#include "spring.h"

#include "stdlib.h"
#include "point.h"

#include "stdio.h"

#include <math.h>

const double tolerance = 0.0005;

double Spring::elasticity = 700;
double Spring::dampening = 5; 

Spring::Spring(Point* p1, Point* p2, double elasticity):
    p1(p1), p2(p2)
{
}

Spring::Spring():
    p1(NULL), p2(NULL)
{

}

double Spring::getElasticity()
{
    return elasticity;
}
double Spring::getDampening()
{
    return dampening;
}
double Spring::setElasticity(double e)
{
    elasticity = e;
}
double Spring::setDampening(double d)
{
    dampening = d;
}
    
Point* Spring::getPoint1()
{
    return this->p1;
}

Point* Spring::getPoint2()
{
    return this->p2;
}

void Spring::calcInertialLength()
{
    this->inertialLength = (p2->getPos() - p1->getPos()).length();
}

static bool intersectSegmentCircle(Vector3 p, Vector3 v, Vector3 c, double r, Vector3* i)
{
    Vector3 vdir = v; vdir.normalize();
    Vector3 circlev = c-p;
    Vector3 projection = (circlev).dot(vdir) * vdir;
    
    Vector3 distance = circlev - projection;
    double dlength = distance.length();
    
    // Outside of circle radius
    if (dlength > r)
    {
        return false;
    }
    
    // Calc length to intersection
    double ilength = sqrt(r*r - dlength*dlength);

    *i = c + distance - vdir * ilength;
    
    if ((i-p).dot(i-p) <= v.dot(v))
    {
        return true;
    }
    return false;
}

void Spring::resolveRigidConstraints(double deltaT)
{    
    Vector3 distance = p2->getPos() - p1->getPos();
    
    double length = distance.length();
    double intensity = length - this->inertialLength;
    
    if (fabs(intensity) < tolerance)
    {
        return;
    }    

    double r = length / this->inertialLength;
    if (r < 0.75)
    {
        intensity = length - (this->inertialLength * 0.75);
    }
    else if (r > 1.25)
    {
        intensity = length - (this->inertialLength * 1.25);    
    }
    else
    {
        return;
    }

    distance.normalize();
    Vector3 diff = distance * (intensity * 0.5);
    p1->displace(diff);
    p2->displace(diff * -1);
}

void Spring::addForces(double deltaT)
{
    Vector3 relvel = p2->getVelocity() - p1->getVelocity();

    Vector3 distance = p2->getPos() - p1->getPos();
    double length = distance.length();
    double intensity = length - this->inertialLength;
    
    if (fabs(intensity) < tolerance)
    {
        return;
    }

    // Take a guess to how the spring is located if length is 0
    if (length < tolerance)
    {
        distance = relvel;
    }

    intensity *= this->elasticity;
   
    distance.normalize();
    relvel = distance * relvel.dot(distance);
    Vector3 dampening = relvel * (this->dampening * deltaT);
    
    p1->addImpulse(distance * intensity - dampening);
    p2->addImpulse(distance * -intensity + dampening);
}
