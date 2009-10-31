#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include "primitives.h"

class Simulator;

class Renderer
{
public:

    Renderer();
    ~Renderer();

    void render(Simulator* sim);
    
    void moveCamera(const Vector3& v); 
    void turnCamera(const double d);
    void tiltCamera(const double d);
    
    
protected:
private:

    Vector3 camPos;
    double camAngleY;
    double camAngleX;
    

};

#endif // PROJECT_RENDERER_H
