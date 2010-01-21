#ifndef PROJECT_PRIMITIVES_H
#define PROJECT_PRIMITIVES_H

class Matrix3;

// 3-dimensional vector class
class Vector3
{

public:
    Vector3(double x, double y, double z);
    Vector3();
    
    Vector3 operator+(const Vector3& vect) const;
    Vector3& operator+=(const Vector3& vect);
    Vector3 operator-(const Vector3& vect) const;
    Vector3& operator-=(const Vector3& vect);
    Vector3 operator*(const double scalar) const;
    Vector3 operator/(const double scalar) const;
    
    double dot(const Vector3& v) const;
    Vector3 cross(const Vector3& v) const;
    
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double v);
    void setY(double v);
    void setZ(double v);
    
    double length() const;
    Vector3& normalize();
    
protected:
private:

    double d[3];
};

// 3-dimensional "rectangle"
class Box
{
public:
    Box(const Vector3& v1, const Vector3& v2);

    Vector3 getV1() const;
    Vector3 getV2() const;
     
    Vector3 v1;
    Vector3 v2;   
    
protected:
private:

};

#endif //PROJECT_PRIMITIVES_H
