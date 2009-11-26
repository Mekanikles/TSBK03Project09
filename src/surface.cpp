#include "surface.h"
#include "stdio.h"

#include "opengl.h"

Surface::Surface(const Vector3& p, const Vector3& v1, const Vector3& v2):
    p(p), v1(v1), v2(v2), restitution(1.0), friction(0.6)
{
    this->normal = v2.cross(v1).normalize();
}

Vector3 Surface::getP() const
{
    return p;
}
Vector3 Surface::getV1() const
{
    return v1;
}
Vector3 Surface::getV2() const
{   
    return v2;
}
Vector3 Surface::getNormal() const
{
    return normal;
}

double Surface::getRestitution()
{
    return restitution;
}

double Surface::getFriction()
{
    return friction;
}
    

bool Surface::isPointInsideBounds(Vector3 point)
{
    Vector3 pvect = point - this->p;
    Vector3 nv1 = v1;
    Vector3 nv2 = v2;
    double d1 = pvect.dot(nv1.normalize());
    double d2 = pvect.dot(nv2.normalize());
 
    if (d1 > v1.length() || d1 < 0.0f)
        return false;
                
    if (d2 > v2.length() || d2 < 0.0f)
        return false;

    return true;
}

double Surface::signedDistanceToPoint(Vector3 point)
{
    Vector3 pvect = point - this->p;
    
    return pvect.dot(this->normal);
}

void Surface::render()
{
    Vector3 p1 = this->p;
    Vector3 p2 = this->p + this->v1;
    Vector3 p3 = this->p + this->v2;
    Vector3 p4 = this->p + this->v1 + this->v2;

    glBegin(GL_QUADS);
    {
        glVertex3d(p1.getX(), p1.getY(), p1.getZ());
        glVertex3d(p2.getX(), p2.getY(), p2.getZ());
        glVertex3d(p4.getX(), p4.getY(), p4.getZ());
        glVertex3d(p3.getX(), p3.getY(), p3.getZ());
    }
    glEnd();
    
    glBegin(GL_LINES);
    {
        glVertex3d(p1.getX(), p1.getY(), p1.getZ());
        glVertex3d(p1.getX()+ this->normal.getX(), p1.getY()+ this->normal.getY(), p1.getZ()+ this->normal.getZ());
    }
    glEnd();
}
