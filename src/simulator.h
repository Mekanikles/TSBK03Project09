#ifndef PROJECT_SIMULATOR_H
#define PROJECT_SIMULATOR_H

#include "linkedlist.h"
#include "shape.h"
#include "surface.h"

class Simulator
{
public:      

    Simulator(double creationTime);
    ~Simulator();

    void tick(double dt);
    void renderShapes();
    void renderSurfaces();
    void attract(Vector3 pos, double strength);
        
    int iterations;
        
protected:
private:
    
    LinkedList<Shape*> shapes;
    LinkedList<Surface*> surfaces;
    
    double currentTime;
    double deltaTime;
        
    void addGravity();
    void collidePoints();
    void addSpringForces();
    
    void applyForces(double deltaT);
    

};



#endif //PROJECT_SIMULATOR_H

