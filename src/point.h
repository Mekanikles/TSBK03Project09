#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H

#include "primitives.h"
#include "linkedlist.h"

class Spring;

class Point
{


public:
    Point(const Vector3& pos, double mass = 1);
    Point();
    
    Vector3 getPos();
    void setPos(const Vector3& new_pos, const Vector3& old_pos);
    void setPos(const Vector3& new_pos);    
    
    void displace(Vector3 d);
    void addForce(Vector3 force);
    void applyForce(double deltaT);

    Vector3 getForce();
    Vector3 getVelocity();
    double getMass();
    void lock(bool set);
    bool isLocked();
    
    
protected:

    Vector3 pos;
    Vector3 old_pos;
    double mass;
    Vector3 force;
    bool locked;
        
    void doVerletStep(double deltaT);
    
private:


};



#endif //PROJECT_POINT_H
