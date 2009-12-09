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
        int indexCount;
        
        void render();
        void renderWireframe();
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
    
        Shape(int pointcount, int indexcount);
        
        Point* points;
        LinkedList<Spring*> springs;
        int* surfaceIndices;
        
        

    private:    
};


#endif //PROJECT_SHAPE_H
