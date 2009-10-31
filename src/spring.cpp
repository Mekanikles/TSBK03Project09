#include "spring.h"

#include "stdlib.h"

Spring::Spring(Point* p1, Point* p2, double elasticity):
    p1(p1), p2(p2), elasticity(elasticity)
{
    
    
}

Spring::Spring():
    p1(NULL), p2(NULL), elasticity(1)
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