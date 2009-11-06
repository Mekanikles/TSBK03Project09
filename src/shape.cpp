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
    
    this->usedpoints = springcount;
    this->usedsprings = pointcount;
}

Shape::~Shape()
{
    delete[] points;
    delete[] springs;
}

void Shape::addAcceleration(Vector3 acc)
{
    for (int i = 0; i < this->pointcount; i++)
    {
        this->points[i].addForce(acc * this->points[i].getMass());
    }
}

void Shape::addSpringForces()
{
    for (int i = 0; i < this->springcount; i++)
    {
        this->springs[i].addForces();
    }
}

void Shape::applyForces(double deltaT)
{
    for (int i = 0; i < this->pointcount; i++)
    {
        this->points[i].applyForce(deltaT);
    }
}

void Shape::collideWithSurface(Surface* s, double deltaT)
{
    for (int i = 0; i < this->pointcount; i++)
    {
        Vector3 pos = this->points[i].getPos();
        if (s->isPointInsideBounds(pos))
        {
            double distance = s->signedDistanceToPoint(pos);
            if (distance < 0.0)
            {
                this->points[i].setPos(this->points[i].getPos() - (s->getNormal() * distance));
                this->points[i].addForce(s->getNormal() * -distance);
            }  
        }
    }
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
