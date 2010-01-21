#include "primitives.h"
#include "stdio.h"
#include "math.h"

Vector3::Vector3(double x, double y, double z)
{
    d[0] = x;
    d[1] = y;
    d[2] = z;
}
Vector3::Vector3()
{
    d[0] = 0.0;
    d[1] = 0.0;
    d[2] = 0.0;
}
    
Vector3 Vector3::operator+(const Vector3& vect) const
{
    return Vector3(this->d[0] + vect.d[0], this->d[1] + vect.d[1], this->d[2] + vect.d[2]);
}

Vector3& Vector3::operator+=(const Vector3& vect)
{
    this->d[0] += vect.d[0];
    this->d[1] += vect.d[1];
    this->d[2] += vect.d[2];
    return *this;
}

Vector3 Vector3::operator-(const Vector3& vect) const
{
    return Vector3(this->d[0] - vect.d[0], this->d[1] - vect.d[1], this->d[2] - vect.d[2]);
}

Vector3& Vector3::operator-=(const Vector3& vect)
{
    this->d[0] -= vect.d[0];
    this->d[1] -= vect.d[1];
    this->d[2] -= vect.d[2];
    return *this;
}

Vector3 Vector3::operator*(const double scalar) const
{
    return Vector3(this->d[0] * scalar, this->d[1] * scalar, this->d[2] * scalar);
}

Vector3 Vector3::operator/(const double scalar) const
{
    return Vector3(this->d[0] / scalar, this->d[1] / scalar, this->d[2] / scalar);
}

double Vector3::dot(const Vector3& v) const
{
    return this->d[0] * v.d[0] + this->d[1] * v.d[1] + this->d[2] * v.d[2];
    
}

Vector3 Vector3::cross(const Vector3& v) const
{   
    Vector3 ret = Vector3(this->d[1] * v.d[2] - v.d[1] * this->d[2], 
                    this->d[2] * v.d[0] -  v.d[2] * this->d[0], 
                    this->d[0] * v.d[1] -  v.d[0] * this->d[1]);
                 
    //fprintf(stderr, "cross: (%f, %f, %f)\n", ret.getX(), ret.getY(), ret.getZ());
    return ret;     
}

double Vector3::getX() const
{
    return this->d[0];
}
double Vector3::getY() const
{
    return this->d[1];
}
double Vector3::getZ() const
{
    return this->d[2];
}    

void Vector3::setX(double v)
{
    this->d[0] = v;
}
void Vector3::setY(double v)
{
    this->d[1] = v;
}
void Vector3::setZ(double v)
{
    this->d[2] = v;
}

double Vector3::length() const
{
    return sqrt(this->d[0] * this->d[0]  + this->d[1] * this->d[1] + this->d[2] * this->d[2]);
}

Vector3& Vector3::normalize()
{
    double len = this->length();
    this->d[0] = this->d[0] / len;
    this->d[1] = this->d[1] / len;
    this->d[2] = this->d[2] / len;
    return *this;
}

Box::Box(const Vector3& v1, const Vector3& v2):
    v1(v1), v2(v2)
{

}

Vector3 Box::getV1() const
{
    return this->v1;
}
Vector3 Box::getV2() const
{
    return this->v2;
}





