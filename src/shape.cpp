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
        this->points[i].addImpulse(acc * this->points[i].getMass());
    }
}

void Shape::addSpringForces(double deltaT)
{
    for (int i = 0; i < this->pointcount; i++)
    {
        this->points[i].addSpringForces(deltaT);
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
            // Distance from point to nearest point on plane
            double distance = s->signedDistanceToPoint(pos);
            if (distance < 0.0)
            {
                Vector3 vel = this->points[i].getVelocity();
                Vector3 normvel = s->getNormal() * vel.dot(s->getNormal());
                Vector3 veltan = vel - normvel;
                
                double r = -distance / normvel.length();
                
                Vector3 intersection = this->points[i].getPos() - vel * r;
                Vector3 pos = this->points[i].getPos();
                
                this->points[i].setPos(intersection + (veltan * r * (1 - s->getFriction())) - (normvel * r * s->getRestitution()),
                                        intersection - veltan * (1-r) * (1 - s->getFriction()) +  normvel * (1-r) * s->getRestitution());
                //this->points[i].setVelocity(normvel * -s->getRestitution() + veltan * (1 - s->getFriction()));
                //this->points[i].setPos(pos - s->getNormal() * distance, pos - s->getNormal() * distance);    
                //this->points[i].setVelocity(Vector3(0,0,0));
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
