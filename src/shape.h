#ifndef PROJECT_SHAPE_H
#define PROJECT_SHAPE_H

#include "linkedlist.h"
#include "primitives.h"
#include "surface.h"

class Point;
class Spring;

class Shape
{
    public:
    
        int pointcount;
        
        virtual void render();
        void addAcceleration(Vector3 acc);
        void addSpringForces();
        void applyForces(double deltaT);
        void collideWithSurface(Surface* s, double deltaT);
        
    protected:
    
        Shape(int pointcount);
        virtual ~Shape();
        
        Point* points;

    private:    
};


#endif //PROJECT_SHAPE_H
