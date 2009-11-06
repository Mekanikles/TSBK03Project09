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
        int springcount;
        
        virtual void render();
        void addAcceleration(Vector3 acc);
        void addSpringForces();
        void applyForces(double deltaT);
        void collideWithSurface(Surface* s, double deltaT);
        
    protected:
    
        Shape(int pointcount, int springcount);
        virtual ~Shape();
        
        Point* points;
        Spring* springs;
        
        int usedpoints;
        int usedsprings;
        
    private:    
};


#endif //PROJECT_SHAPE_H
