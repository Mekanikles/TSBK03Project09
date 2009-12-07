#ifndef PROJECT_SPRING_H
#define PROJECT_SPRING_H

#include "primitives.h"

class Point;

class Spring
{
public:
    
    Spring(Point* p1, Point* p2, double elasticity = 1.0);
    Spring();
    
    Point* getPoint1();
    Point* getPoint2();
    
    void addForces(double deltaT);
    bool resolveRigidConstraints(double deltaT);
    
    void calcInertialLength();
    
    static double getElasticity();
    static double getDampening();
    static void setElasticity(double e);
    static void setDampening(double d);
        
    static double getMaxlength();
    static double getMinlength();
    static void setMaxlength(double max);
    static void setMinlength(double min);
    
    static void setRigidSprings(bool enable);
    
    
protected:
private:
    
    Point* p1;
    Point* p2;
    Vector3 old_dist;
    double inertialLength;
    
    static double elasticity;
    static double dampening; 
    static double maxlength;
    static double minlength;
  
    static bool rigidSprings;
  
};  


#endif //PROJECT_SPRING_H
