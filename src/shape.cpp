#include "shape.h"

#include "opengl.h"

#include "primitives.h"
#include "point.h"
#include "spring.h"

#include "stdio.h"

Shape::Shape(int pointcount, int indexCount):
    pointcount(pointcount), indexCount(indexCount)
{
    points = new Point[pointcount];
    surfaceIndices = new int[indexCount];
    fprintf(stderr, "Shape: indexcount: %i\n", this->indexCount);
    for (int i = 0; i < this->indexCount; i++)
    {
            surfaceIndices[i] = 0;
    }

}

Shape::~Shape()
{
    delete[] points;
    delete surfaceIndices;
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

bool Shape::resolveRigidConstraints(double deltaT)
{
    bool retval = true;
    for (Node<Spring*>* s = this->springs.getFirst(); s != NULL; s = s->next)
    {
        retval &= s->item->resolveRigidConstraints(deltaT);
    }
    return retval;
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

void Shape::collideWithSurfaceMap(Surface* map, double deltaT)
{
    
    for (int i = 0; i < this->pointcount; i++)
    {
    
        //for (int b = 0; b < 10*10*2; b++)
        {
        Vector3 pos = this->points[i].getPos();
    
        int x = (int)((pos.getX() + 50 - 5) / 10);
        int z = (int)((pos.getZ() + 50 - 5) / 10);
        if (x > 9)
            x = 9;
        if (x < 0) 
            x = 0;
        if (z > 9)
            z = 9;
        if (z < 0) 
            z = 0;
    
    
        
    
        int k = 1;
        if ((pos.getX() + 50 - 5 - (double)x * 10) + (pos.getZ() + 50 - 5 - (double)z * 10) <= 10)
            k = 0;
        
       
        Surface* s = &map[z * 10 * 2 + x * 2 + k];
        //Surface* s = &map[b];
        
        // Distance from point to nearest point on plane
        double distance = s->signedDistanceToPoint(pos);
            
        // If distance is negative, point is behind plane
        if (distance < 0.0)
        {        

            //fprintf(stderr, "distance: %f x:%i, z:%i, posx:%f, posz:%f, surfP(%f, %f, %f), surfV1(%f, %f, %f), surfV2(%f, %f, %f)\n\n", distance, x, z, pos.getX(), pos.getZ(), s->getP().getX(), s->getP().getY(), s->getP().getZ(), s->getV1().getX(), s->getV1().getY(), s->getV1().getZ(), s->getV2().getX(), s->getV2().getY(), s->getV2().getZ());  
            //fprintf(stderr, "K: %i\n", k);
            // Check if point is within surface bounds
            //if (s->isPointInsideBounds(pos))
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
                
                Vector3 pos = this->points[i].getPos();
                this->points[i].setPos(pos - s->getNormal() * distance, pos - s->getNormal() * distance);    
                
                // Move to intersecion point. Conserve velocity accounting for friciton and restitution.
                // Since verlets are used, new velocity are forced by explicitly setting the old position
                //this->points[i].setPos(intersection + (veltan * r * (1 - s->getFriction())) - (normvel * r * s->getRestitution()),
                                        //intersection - veltan * (1-r) * (1 - s->getFriction()) +  normvel * (1-r) * s->getRestitution());
                
                //this->points[i].setVelocity(normvel * -s->getRestitution() + veltan * (1 - s->getFriction()));
                //this->points[i].setPos(pos - s->getNormal() * distance, pos - s->getNormal() * distance);    
                //this->points[i].setVelocity(Vector3(0,0,0));
            }  
        }
        }
    }
}


void Shape::render()
{
    Vector3 pos1;
    Vector3 pos2;
    Vector3 pos3;
    Vector3 norm;
    Vector3 norm1;
    Vector3 norm2;
    Vector3 norm3;
    
    for (int i = 0; i < this->indexCount; i+=3)
    {
        
        pos1 = this->points[this->surfaceIndices[i]].getPos();
        pos2 = this->points[this->surfaceIndices[i+1]].getPos();
        pos3 = this->points[this->surfaceIndices[i+2]].getPos();
        
        norm = (pos2-pos1).cross(pos3-pos1);
        this->points[this->surfaceIndices[i]].setNormal(norm);
    }

    glBegin(GL_TRIANGLES);
    { 
    
        for (int i = 0; i < this->indexCount; i+=3)
        {
            
            pos1 = this->points[this->surfaceIndices[i]].getPos();
            pos2 = this->points[this->surfaceIndices[i+1]].getPos();
            pos3 = this->points[this->surfaceIndices[i+2]].getPos();
            norm1 = this->points[this->surfaceIndices[i]].getNormal();
            norm2 = this->points[this->surfaceIndices[i+1]].getNormal();
            norm3 = this->points[this->surfaceIndices[i+2]].getNormal();
         
            glNormal3f(norm1.getX(), norm1.getY(), norm1.getZ());
            glVertex3d(pos1.getX(), pos1.getY(), pos1.getZ());
            glNormal3f(norm2.getX(), norm2.getY(), norm2.getZ());
            glVertex3d(pos2.getX(), pos2.getY(), pos2.getZ());
            glNormal3f(norm3.getX(), norm3.getY(), norm3.getZ());
            glVertex3d(pos3.getX(), pos3.getY(), pos3.getZ());
        }
    }
    glEnd();        
}

void Shape::renderWireframe()
{
    Vector3 pos;
    Vector3 pos2;
    
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < this->pointcount; i++)
        {

            pos = this->points[i].getPos();
            glVertex3d(pos.getX(), pos.getY(), pos.getZ());
        
        }
    }
    glEnd();
        
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
