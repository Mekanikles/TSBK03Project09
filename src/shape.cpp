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


void Shape::addSpring(Point* p1, Point* p2)
{
    //fprintf(stderr, "Adding spring between %p\n", p1);
    for (Node<Spring*>* s = this->springs.getFirst(); s != NULL; s = s->next)
    {
        //fprintf(stderr, "New point: %p, compare to existing spring( %p, %p)\n", p, s->item->getPoint1(), s->item->getPoint2());
    
        if (s->item->getPoint1() == p1 && s->item->getPoint2() == p2)
            return;
            
        if (s->item->getPoint1() == p2 && s->item->getPoint2() == p1)
            return;
    }
    Spring* s = new Spring(p1, p2);
    this->springs.addFirst(s);
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
    for (Node<Spring*>* s = this->springs.getFirst(); s != NULL; s = s->next)
    {
        s->item->addForces(deltaT);
    }
}

void Shape::resolveRigidConstraints(double deltaT)
{
    for (Node<Spring*>* s = this->springs.getFirst(); s != NULL; s = s->next)
    {
        s->item->resolveRigidConstraints(deltaT);
    }
}

void Shape::setupSprings()
{
    for (Node<Spring*>* s = this->springs.getFirst(); s != NULL; s = s->next)
    {
        s->item->calcInertialLength();
    }
}

LinkedList<Spring*>* Shape::getSpringList()
{
    return &this->springs;
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
        
        // Distance from point to nearest point on plane
        double distance = s->signedDistanceToPoint(pos);
            
        // If distance is negative, point is behind plane
        if (distance < 0.0)
        {        
            // Check if point is within surface bounds
            if (s->isPointInsideBounds(pos))
            {       
                // Point velocity
                Vector3 vel = this->points[i].getVelocity();
                // Velocity along surface normal
                Vector3 normvel = s->getNormal() * vel.dot(s->getNormal());
                // Velocity along surface plane
                Vector3 veltan = vel - normvel;
                
                // Ratio of velocity that intersects the plane
                double r = -distance / normvel.length();
                
                Vector3 intersection;
                // Make sure ratio isn't too big
                if (r > 10000.0)
                {
                    intersection = this->points[i].getPos() - s->getNormal() * distance - veltan;
                    r = 1.0;
                }
                else
                {
                    // Calculate intersection point from ratio
                    intersection = this->points[i].getPos() - s->getNormal() * distance - veltan * r;
                }
                
                //Vector3 pos = this->points[i].getPos();
                //this->points[i].setPos(pos - s->getNormal() * distance, pos - s->getNormal() * distance);    
                
                // Move to intersecion point. Conserve velocity accounting for friciton and restitution.
                // Since verlets are used, new velocity are forced by explicitly setting the old position
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
    }

    LinkedList<Spring*>* springs = this->getSpringList();
    glBegin(GL_LINES);
    {
        for (Node<Spring*>* s = springs->getFirst(); s != NULL; s = s->next)
        {
            pos = s->item->getPoint1()->getPos();
            pos2 = s->item->getPoint2()->getPos();
            
            glVertex3d(pos.getX(), pos.getY(), pos.getZ());
            glVertex3d(pos2.getX(), pos2.getY(), pos2.getZ());            
        }
    }   
    glEnd();
    
    
}
