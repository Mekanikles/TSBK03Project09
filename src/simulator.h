#ifndef PROJECT_SIMULATOR_H
#define PROJECT_SIMULATOR_H

#include "linkedlist.h"
#include "shape.h"
#include "surface.h"

#define MAPSIZEX 10
#define MAPSIZEY 10

class Simulator
{
public:      

    Simulator();
    ~Simulator();

    void tick(double dt);
    void renderShapes(bool wireframe);
    void renderSurfaces(bool wireframe);
    void resetShape(int id, double size);
    void attract(Vector3 pos, double strength);
        
    int iterations;
    
    void setRigidSprings(bool enable);
        
protected:
private:
    
    LinkedList<Shape*> shapes;
    LinkedList<Surface*> surfaces;
    Surface surfacemap[MAPSIZEX * MAPSIZEY *2];
    
    double currentTime;
    double deltaTime;

    bool rigidSprings;
         
    void addGravity();
    void collidePoints();
    void addSpringForces();
    bool resolveRigidConstraints();
    
    void applyForces(double deltaT);

};



#endif //PROJECT_SIMULATOR_H

