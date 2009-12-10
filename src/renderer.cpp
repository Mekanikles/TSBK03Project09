#include "renderer.h"

#include "simulator.h"

#include "opengl.h"
#include "shader.h"

#include "math.h"

Renderer::Renderer()
{
    fprintf(stderr, "Creating renderer\n");

    camPos = Vector3(0,2,16);
    camAngleX = 0;
    camAngleY = 0;
    wireframe = false;


    this->shapeShader = new Shader("test.vert", "test.frag");
    this->worldShader = new Shader("spec.vert", "spec.frag");
    this->borderShader = new Shader("border.vert", "border.frag");
}

Renderer::~Renderer()
{
    
    delete this->shapeShader;
    delete this->borderShader;
    delete this->worldShader;
}

void Renderer::render(Simulator* sim)
{
    glLoadIdentity();
    gluPerspective(70, 4/3, 0.1, 300);
 
    glRotated(camAngleY, 1, 0, 0);
    glRotated(camAngleX, 0, 1, 0);    
    glTranslated(-this->camPos.getX(), -this->camPos.getY(), -this->camPos.getZ());
     
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Render border
    /*
    if (!this->wireframe)
    {
        glColor4f(0, 0, 0, 1);
        glDepthFunc (GL_LESS);
        //borderShader->activate();
        glLineWidth(2);
        glPolygonMode (GL_BACK, GL_LINE);
        glCullFace(GL_FRONT);
        sim->renderShapes(false);
        
        glCullFace(GL_BACK);
        glPolygonMode (GL_BACK, GL_FILL);
        //borderShader->deactivate();
        glDepthFunc (GL_LEQUAL);
        
    }
    */
    
    if (!this->wireframe)
        shapeShader->activate();    
    
    // Render simulation shapes  
    // Render normally
    glPointSize(6);
    glLineWidth(1);
    glColor4f(1, 0, 0, 1);
    sim->renderShapes(this->wireframe);
    
    shapeShader->deactivate();
    
    
    // Draw floor
    glColor4f(1, 1, 1, 0.4);
    glBegin(GL_QUADS);
    {
        glVertex3d(this->camPos.getX() - 1000, 0, this->camPos.getZ() - 1000);
        glVertex3d(this->camPos.getX() - 1000, 0, this->camPos.getZ() + 1000);
        glVertex3d(this->camPos.getX() + 1000, 0, this->camPos.getZ() + 1000);
        glVertex3d(this->camPos.getX() + 1000, 0, this->camPos.getZ() - 1000);   
    }
    glEnd();

    glTranslated(0, 0.01, 0);

    if (!this->wireframe)
        worldShader->activate();

    // Render simulation surfaces
    glColor4f(1, 0, 0.7, 0.5);
    sim->renderSurfaces(this->wireframe);
    
   
    worldShader->deactivate();
    
    glTranslated(0, 0.01, 0);
    
    // Render shadow
    glTranslated(0, 0.001, 0);
    glLineWidth(2);
    glPointSize(8);
    glColor4f(0, 0, 0, 0.3);
    glScaled(1, 0, 1);
    sim->renderShapes(this->wireframe);
 

}


void Renderer::moveCamera(const Vector3& v)
{
    Vector3 rotv;

    double angle  = -camAngleX  * M_PI/180;
    rotv = Vector3(cos(angle) * v.getX() + sin(angle) * v.getZ(), v.getY(), -sin(angle) * v.getX() + cos(angle) * v.getZ());

    camPos = camPos + rotv;
    if (camPos.getY() < 0.5)
        camPos.setY(0.5);
}
    
void Renderer::turnCamera(const double d)
{
    camAngleX+=d;
}

void Renderer::tiltCamera(const double d)
{
    camAngleY+=d;
}
    
bool Renderer::setWireframe(bool enabled)
{
    this->wireframe = enabled;
}

double Renderer::getCameraTurnAngle()
{
    return this->camAngleX;
}



