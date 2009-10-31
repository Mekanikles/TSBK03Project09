#include "shape.h"

#include "opengl.h"

#include "primitives.h"
#include "point.h"
#include "spring.h"

#include "stdio.h"

Shape::Shape(int pointcount, int springcount):
    pointcount(pointcount), springcount(springcount)
{
    points = new Point[pointcount];
    springs = new Spring[springcount];
    
}

Shape::~Shape()
{
    delete[] points;
    delete[] springs;
}


void Shape::render()
{
    Vector3 pos;

    glBegin(GL_POINTS);
    {
        for (int i = 0; i < this->pointcount; i++)
        {
            pos = this->points[i].getPos();
            glVertex3d(pos.getX(), pos.getY(), pos.getZ());
            //fprintf(stderr, "render: x: %f, y: %f z: %f\n", pos.getX(), pos.getY(), pos.getZ());
        }
    }
    glEnd();        
    glBegin(GL_LINES);
    {
        for (int i = 0; i < this->springcount; i++)
        {
            pos = this->springs[i].getPoint1()->getPos();
            glVertex3d(pos.getX(), pos.getY(), pos.getZ());
            pos = this->springs[i].getPoint2()->getPos();
            glVertex3d(pos.getX(), pos.getY(), pos.getZ());            
        }
    }   
    glEnd();
}
