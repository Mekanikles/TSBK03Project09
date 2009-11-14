#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H

#include "primitives.h"
#include "linkedlist.h"

class Spring;

class Point
{


public:
    Point(const Vector3& pos, double mass = 1.0);
    Point();
    
    Vector3 getPos();
    void setPos(const Vector3& pos);
    void addImpulse(Vector3 impulse);
    void applyForce(double deltaT);
    Vector3 getImpulse();
    Vector3 getVelocity();
    double getMass();
    void Lock(bool set);
    bool isLocked();
    
    LinkedList<Spring*>* getSpringList();
    void addNeighbor(Point* p, double elasticity = 1.0);
    void addSpringForces();
    void setupSprings();
    
protected:

    Vector3 pos;
    Vector3 old_pos;
    double mass;
    Vector3 velocity;
    Vector3 impulse;
    bool locked;
    
    LinkedList<Spring*> springs;
    
    
private:


};



#endif //PROJECT_POINT_H
