#include "spring.h"

#include "stdlib.h"
#include "point.h"

#include "stdio.h"

#include <math.h>

const double tolerance = 0.0005;

Spring::Spring(Point* p1, Point* p2, double elasticity):
    p1(p1), p2(p2), elasticity(elasticity), inertialLength(0)
{
}

Spring::Spring():
    p1(NULL), p2(NULL), elasticity(1), inertialLength(0)
{

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

void Spring::addForces()
{
    Vector3 relvel = p2->getVelocity() - p1->getVelocity();

    //fprintf(stderr, "p1 pos: (%f, %f, %f),\n p2 pos: (%f, %f, %f)\n", p1->getPos().getX(), p1->getPos().getY(), p1->getPos().getZ(), p2->getPos().getX(), p2->getPos().getY(), p2->getPos().getZ());

    Vector3 distance = p2->getPos() - p1->getPos();
    double length = distance.length();

    // Take a guess to how the spring is located if length is 0
    if (length < tolerance)
    {
        distance = relvel;
    }

    distance.normalize();

    //fprintf(stderr, "old length: %f\n", (float)(this->length)); 
    //fprintf(stderr, "new length: %f\n", (float)(inertialLength)); 

    if (fabs(this->inertialLength - length) < tolerance)
    {
        return;
    }
    
    double intensity = this->inertialLength - length;
   
    // Prevent explosions
    if (intensity > 1.0)
        intensity = 1.0;
        
    if (intensity < -1.0)
        intensity = -1.0;

    intensity *= this->elasticity * 1000;
   
    relvel = distance * relvel.dot(distance);
    
    
    
    //fprintf(stderr, "intensity: %f\n\n", intensity);
    p1->addImpulse(distance * -intensity + relvel * 0.4);
    //p2->addImpulse(distance * intensity - relvel * 0.1);
}
