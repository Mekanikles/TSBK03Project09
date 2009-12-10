#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include "primitives.h"

class Simulator;
class Shader;

class Renderer
{
public:

    Renderer();
    ~Renderer();

    void render(Simulator* sim);
    
    void moveCamera(const Vector3& v); 
    void turnCamera(const double d);
    void tiltCamera(const double d);
    
    bool setWireframe(bool enabled);
    double getCameraTurnAngle();
    
protected:
private:

    Vector3 camPos;
    double camAngleY;
    double camAngleX;
    
    bool wireframe;    

    Shader* worldShader;
};

#endif // PROJECT_RENDERER_H
