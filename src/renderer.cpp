#include "renderer.h"

#include "simulator.h"

#include "opengl.h"

Renderer::Renderer()
{
    fprintf(stderr, "Creating renderer");

    camPos = Vector3(0,2,16);
    camAngleX = 0;
    camAngleY = 0;

    fprintf(stderr, ".\n");
}

Renderer::~Renderer()
{
    

}

void Renderer::render(Simulator* sim)
{
    glLoadIdentity();
    gluPerspective(70, 4/3, 0.1, 100);
 
    glRotated(camAngleY, 1, 0, 0);
    glRotated(camAngleX, 0, 1, 0);    
    glTranslated(-this->camPos.getX(), -this->camPos.getY(), -this->camPos.getZ());
     
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    // Render simulation shapes
    glLineWidth(1);
    glPointSize(6);
    glColor4f(1, 0, 0, 1);
    sim->renderShapes();
    
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

    glTranslated(0, 0.001, 0);

    // Render simulation surfaces
    glColor4f(1, 0, 0.7, 0.5);
    sim->renderSurfaces();
    
    // Render shadow
    glTranslated(0, 0.001, 0);
    glLineWidth(2);
    glPointSize(8);
    glColor4f(0, 0, 0, 0.3);
    glScaled(1, 0, 1);
    sim->renderShapes();
 

}


void Renderer::moveCamera(const Vector3& v)
{
    camPos = camPos + v;
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
    




