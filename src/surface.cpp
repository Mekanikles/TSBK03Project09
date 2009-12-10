#include "surface.h"
#include "stdio.h"

#include "opengl.h"

double Surface::friction = 1.0;
    
Surface::Surface()
{
}

Surface::Surface(const Vector3& p, const Vector3& v1, const Vector3& v2):
    p(p), v1(v1), v2(v2)
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

double Surface::getFriction()
{
    return friction;
}
    

void Surface::setFriction(double f)
{
    friction = f;
}
    
bool Surface::isPointInsideBounds(Vector3 point)
{
    Vector3 pvect = point - this->p;
    double d1 = pvect.dot(v1) / this->v1.dot(this->v1);
    double d2 = pvect.dot(v2) / this->v2.dot(this->v2);
 
    if (d1 < 0.0 || d2 < 0.0 || (d1 + d2 > 1))
        return false;

    return true;
}

double Surface::signedDistanceToPoint(Vector3 point)
{
    Vector3 pvect = point - this->p;
    
    return pvect.dot(this->normal);
}

void Surface::renderWireframe()
{
    Vector3 p1 = this->p;
    Vector3 p2 = this->p + this->v1;
    Vector3 p3 = this->p + this->v2;
    Vector3 p4 = this->p + this->v1 + this->v2;

    glBegin(GL_LINE_STRIP);
    {
        glVertex3d(p1.getX(), p1.getY(), p1.getZ());
        glVertex3d(p3.getX(), p3.getY(), p3.getZ());
        glVertex3d(p2.getX(), p2.getY(), p2.getZ());
        glVertex3d(p1.getX(), p1.getY(), p1.getZ());
        glVertex3d(p1.getX()+ this->normal.getX(), p1.getY()+ this->normal.getY(), p1.getZ()+ this->normal.getZ());
    }
    glEnd();
}

void Surface::render()
{
    Vector3 p1 = this->p;
    Vector3 p2 = this->p + this->v1;
    Vector3 p3 = this->p + this->v2;
    Vector3 norm;
    
    
    glBegin(GL_TRIANGLES);
    {
        norm = (p3-p1).cross(p2-p1);
        norm.normalize();
        glNormal3f(norm.getX(), norm.getY(), norm.getZ());
        glVertex3d(p1.getX(), p1.getY(), p1.getZ());
        glVertex3d(p3.getX(), p3.getY(), p3.getZ());
        glVertex3d(p2.getX(), p2.getY(), p2.getZ());
    }
    glEnd();
}