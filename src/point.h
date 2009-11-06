#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H

#include "primitives.h"

class Point
{


public:
    Point(const Vector3& pos, double mass = 1.0);
    Point();
    
    Vector3 getPos();
    void setPos(const Vector3& pos);
    void addForce(Vector3 force);
    void applyForce(double deltaT);
    Vector3 getForce();
    Vector3 getVelocity();
    double getMass();
    void Lock(bool set);
    bool isLocked();
    
protected:

    Vector3 pos;
    Vector3 old_pos;
    double mass;
    Vector3 force;
    bool locked;
    
private:


};



#endif //PROJECT_POINT_H
