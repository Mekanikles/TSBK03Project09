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


    this->worldShader = new Shader("diff.vert", "diff.frag");
}

Renderer::~Renderer()
{
    delete this->worldShader;
}

void Renderer::render(Simulator* sim)
{
    glLoadIdentity();
    gluPerspective(70, 4/3, 0.1, 200);
 
    glRotated(camAngleY, 1, 0, 0);
    glRotated(camAngleX, 0, 1, 0);    
    glTranslated(-this->camPos.getX(), -this->camPos.getY(), -this->camPos.getZ());
     
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    if (!this->wireframe)
        worldShader->activate();    
    
    // Render simulation shapes  
    // Render normally
    glPointSize(6);
    glLineWidth(1);
    glColor4f(1, 0, 0, 1);
    sim->renderShapes(this->wireframe);
    
    worldShader->deactivate();

    // Render surface mesh.
    // Since antialiasing for lines is turned on, and the background is black, 
    // this will create a cel-shade-style border around the shape
    if (!this->wireframe)
    {
        glColor4f(0, 0, 0, 0.1);
        glLineWidth(4);
        glPolygonMode (GL_FRONT, GL_LINE);
        glCullFace(GL_BACK);
        sim->renderShapes(false);
        glCullFace(GL_BACK);
        glPolygonMode (GL_FRONT, GL_FILL);
    }
    
    if (!this->wireframe)
        worldShader->activate();
    
    // Draw floor
    glDepthFunc (GL_LESS);
    glColor4f(0.7, 0.7, 1, 1);
    glBegin(GL_QUADS);
    {
        glNormal3d(0,1,0);
        glVertex3d(this->camPos.getX() - 1000, -1, this->camPos.getZ() - 1000);
        glVertex3d(this->camPos.getX() - 1000, -1, this->camPos.getZ() + 1000);
        glVertex3d(this->camPos.getX() + 1000, -1, this->camPos.getZ() + 1000);
        glVertex3d(this->camPos.getX() + 1000, -1, this->camPos.getZ() - 1000);   
    }
    glEnd();
    glDepthFunc (GL_LEQUAL);
    glTranslated(0, 0.01, 0);
    
    // Render simulation surfaces
    glColor4f(0, 0.5, 0.7, 1.0);
    sim->renderSurfaces(this->wireframe);
 
    glColor4f(1.0, 1.0, 1.0, 0.7);
    if (!this->wireframe)
    {
        glPolygonMode (GL_FRONT, GL_LINE);
        glLineWidth(3);
        sim->renderSurfaces(this->wireframe);
        
        glPolygonMode (GL_FRONT, GL_FILL);
    }
       
    worldShader->deactivate();
    
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



