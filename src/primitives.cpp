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
    
Vector3 Vector3::operator+(const Vector3& vect)
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

Vector3 Vector3::operator-(const Vector3& vect)
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

Vector3 Vector3::operator*(const double scalar)
{
    return Vector3(this->d[0] * scalar, this->d[1] * scalar, this->d[2] * scalar);
}

Vector3 Vector3::operator/(const double scalar)
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
                 
    fprintf(stderr, "cross: (%f, %f, %f)\n", ret.getX(), ret.getY(), ret.getZ());
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


Matrix3::Matrix3(double x1, double x2, double x3, double y1, double y2, double y3, double z1, double z2, double z3)
{
    this->d[0][0] = x1; this->d[1][0] = x2; this->d[2][0] = x3;
    this->d[0][1] = y1; this->d[1][1] = y2; this->d[2][1] = y3;
    this->d[0][2] = z1; this->d[1][2] = z2; this->d[2][2] = z3;
}
Matrix3::Matrix3()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->d[i][j] = 0.0;
}

Vector3 Matrix3::operator*(const Vector3& vect)
{
    Vector3 v;
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            v.d[j] += this->d[j][i]*vect.d[j];

    return v;
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





