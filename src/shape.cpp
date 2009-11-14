#include "shape.h"

#include "opengl.h"

#include "primitives.h"
#include "point.h"
#include "spring.h"

#include "stdio.h"

Shape::Shape(int pointcount):
    pointcount(pointcount)
{
    points = new Point[pointcount];
   
}

Shape::~Shape()
{
    delete[] points;
}

void Shape::addAcceleration(Vector3 acc)
{
    for (int i = 0; i < this->pointcount; i++)
    {
        this->points[i].addImpulse(acc);
    }
}

void Shape::addSpringForces()
{
    for (int i = 0; i < this->pointcount; i++)
    {
        this->points[i].addSpringForces();
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
                double impulse = this->points[i].getVelocity().dot(s->getNormal());
                this->points[i].addImpulse(s->getNormal() * -impulse * s->getRestitution());
                Vector3 friction = (this->points[i].getVelocity() - (s->getNormal() * impulse)) * -s->getFriction();
                this->points[i].addImpulse(friction);
                
            }  
        }
    }
}


void Shape::render()
{
    Vector3 pos;
    Vector3 pos2;
    
    for (int i = 0; i < this->pointcount; i++)
    {

        glBegin(GL_POINTS);
        {
            pos = this->points[i].getPos();
            glVertex3d(pos.getX(), pos.getY(), pos.getZ());
        }
        glEnd();        
        
        LinkedList<Spring*>* springs = this->points[i].getSpringList();
        glBegin(GL_LINES);
        {
            for (Node<Spring*>* s = springs->getFirst(); s != NULL; s = s->next)
            {
                pos2 = pos - s->item->getPoint2()->getPos();
                pos2 = pos - pos2 * 0.5;
                glVertex3d(pos.getX(), pos.getY(), pos.getZ());
                glVertex3d(pos2.getX(), pos2.getY(), pos2.getZ());            
            }
        }   
        glEnd();
        
    }
}
