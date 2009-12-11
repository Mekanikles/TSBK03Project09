#include "spring.h"

#include "stdlib.h"
#include "point.h"

#include "stdio.h"

#include <math.h>

const double tolerance = 0.0005;

double Spring::elasticity = 700;
double Spring::dampening = 10; 

double Spring::maxlength = 1.1;
double Spring::minlength = 0.70;

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
void Spring::setElasticity(double e)
{
    elasticity = e;
}
void Spring::setDampening(double d)
{
    dampening = d;  
}
    
double Spring::getMaxlength()
{
    return maxlength;
}
double Spring::getMinlength()
{
    return minlength;
}
void Spring::setMaxlength(double max)
{
    maxlength = max;
}
void Spring::setMinlength(double min)
{
    minlength = min;
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
    this->old_dist = (p2->getPos() - p1->getPos()); 
    this->inertialLength = this->old_dist.length();
}

// Finds the first intersection point between a sphere and a segment. Assume the segment always starts outside the sphere.
static bool intersectSegmentCircle(Vector3 p, Vector3 v, Vector3 c, double r, Vector3* i)
{
    Vector3 vdir = v; vdir.normalize();
    Vector3 diff = c - p;
    double vlen2 = v.dot(v);
    if (vlen2 == 0.0)
    {
        return false;
    }
    double t = diff.dot(v) / v.dot(v);
    // Ignore outward-directed segments
    if (t < 0.0)
    {
        return false;
    }
    double t2 = t;
    
    if (t < 0.0)
        t = 0.0;
    if (t > 1.0)
        t = 1.0;
    Vector3 closest = p + v * t;
    Vector3 d = c - closest;
    double distsqr = d.dot(d);
    
    
    if (distsqr >= r * r)
    {
        return false;
    }

    // Orthogonal closest point
    if (t2 > 1.0 || t2 < 0.0)
    {
        closest = p + v * t2;
        d = c - closest;
            distsqr = d.dot(d);
    }

    // Calc length to intersection
    double ilength = sqrt(r*r - distsqr);
    
    *i = closest - vdir * ilength;
    
    //fprintf(stderr, "p(%f, %f, %f), v(%f, %f, %f), i(%f, %f, %f)\n", p.getX(), p.getY(), p.getZ(), v.getX(), v.getY(), v.getZ(), i->getX(), i->getY(), i->getZ());
    //fprintf(stderr, "dissqr: %f, r^2: %f, t2: %f, vlen2: %f, ilength: %f\n", distsqr, r*r, t2, vlen2, ilength);
    
    return true;
}

bool Spring::resolveRigidConstraints(double deltaT)
{    
    Vector3 distance = p2->getPos() - p1->getPos();
    
    double length = distance.length();
    double intensity = length - this->inertialLength;
    
    if ((distance - old_dist).length() < 0.05*this->inertialLength)//(fabs(intensity) < tolerance)
    {
        //this->old_dist = p2->getPos() - p1->getPos();
        //fprintf(stderr, "lol\n");
        return true;
    }    

    Vector3 goal = distance;

    double r = length / this->inertialLength;

    
    if (r > this->maxlength)
    { 
        Vector3 distnorm = distance; distnorm.normalize();
        goal = distnorm * (this->inertialLength * this->maxlength);
    }
    else if (r < this->minlength)
    {
        /*if (intersectSegmentCircle(old_dist, distance - old_dist, Vector3(0,0,0), this->inertialLength * minlength * 1, &goal))
        {   
            //fprintf(stderr, "flag!\n");
            Vector3 diff = ((distance - goal) * 0.5);
            p1->displace(diff);
            p2->displace(diff * -1);
            return;
        }
        else
        */
        {
            Vector3 distnorm = distance; distnorm.normalize();
            goal = distnorm * (this->inertialLength * this->minlength);
        }
    }
    else
    {
        this->old_dist = p2->getPos() - p1->getPos();
        return true;
    }

    Vector3 diff = ((distance - goal) * 0.5);
    p1->displace(diff);
    p2->displace(diff * -1);        
    this->old_dist = p2->getPos() - p1->getPos();
    return false;
}

void Spring::addForces(double deltaT)
{
    Vector3 relvel = this->p2->getVelocity() - this->p1->getVelocity();

    Vector3 distance = this->p2->getPos() - this->p1->getPos();
    double length = distance.length();
    double intensity = length - this->inertialLength;
    
    if (fabs(intensity) < tolerance)
        return;

    // Take a guess to how the spring is located if length is 0
    if (length < tolerance)
        distance = relvel;

    intensity *= this->elasticity;
    distance.normalize();
    
    // Damping
    relvel = distance * relvel.dot(distance);
    Vector3 dampening = relvel * (this->dampening * deltaT);
    
    this->p1->addImpulse(distance * intensity - dampening);
    this->p2->addImpulse(distance * -intensity + dampening);
}
