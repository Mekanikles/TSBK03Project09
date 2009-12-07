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
        void applyForces(double deltaT);
        void collideWithSurfaceMap(Surface* map, double deltaT);
        
        virtual ~Shape();    


        LinkedList<Spring*>* getSpringList();
        void addSpring(Point* p1, Point* p2);
        void addSpringForces(double deltaT);
        bool resolveRigidConstraints(double deltaT);
        void setupSprings();    
        
    protected:
    
        Shape(int pointcount);
        
        Point* points;
        LinkedList<Spring*> springs;
        LinkedList<Surface*> surfaces;
        
        

    private:    
};


#endif //PROJECT_SHAPE_H
