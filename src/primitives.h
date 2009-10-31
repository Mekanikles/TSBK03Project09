#ifndef PROJECT_PRIMITIVES_H
#define PROJECT_PRIMITIVES_H

class Matrix3;


class Vector3
{
    friend class Matrix3;

public:
    Vector3(double x, double y, double z);
    Vector3();
    
    Vector3 operator+(const Vector3& vect);
    Vector3 operator-(const Vector3& vect);
    
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double v);
    void setY(double v);
    void setZ(double v);
    
protected:
private:

    double d[3];
};

class Matrix3
{
public:
    Matrix3(double x1, double x2, double x3, double y1, double y2, double y3, double z1, double z2, double z3);
    Matrix3();

    static Matrix3 createRotation(Vector3 vect);

    Vector3 operator*(const Vector3& vect)

protected:
private:
    
    double d[3][3];
}



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
