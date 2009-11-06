#include "spring.h"

#include "stdlib.h"
#include "point.h"

#include "stdio.h"

#include <math.h>

const double tolerance = 0.000005;

Spring::Spring(Point* p1, Point* p2, double elasticity):
    p1(p1), p2(p2), elasticity(elasticity), length(0)
{
}

Spring::Spring():
    p1(NULL), p2(NULL), elasticity(1), length(0)
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
    this->length = (p2->getPos() - p1->getPos()).length();
}

void Spring::addForces()
{
    Vector3 relvel = p2->getVelocity() - p1->getVelocity();

    Vector3 distance = p2->getPos() - p1->getPos();
    double inertialLength = distance.length();

    //fprintf(stderr, "old length: %f\n", (float)(this->length)); 
    //fprintf(stderr, "new length: %f\n", (float)(inertialLength)); 

    if (fabs(this->length - inertialLength) < tolerance)
    {
        return;
    }
    
    
    double intensity = this->elasticity * (this->length - inertialLength) * 50;
    distance.normalize();

    //fprintf(stderr, "intensity: %f\n", intensity);
    p1->addForce(distance * -intensity - relvel * 0.1);
    p2->addForce(distance * intensity + relvel * 0.1);
}
