#ifndef PROJECT_SPRING_H
#define PROJECT_SPRING_H

class Point;

class Spring
{
public:
    
    Spring(Point* p1, Point* p2, double elasticity = 1.0);
    Spring();
    
    Point* getPoint1();
    Point* getPoint2();
    
    void addForces(double deltaT);
    void resolveRigidConstraints(double deltaT);
    
    void calcInertialLength();
    
    static double getElasticity();
    static double getDampening();
    static double setElasticity(double e);
    static double setDampening(double d);
        
    
    
protected:
private:
    
    Point* p1;
    Point* p2;    
    double inertialLength;
    
    static double elasticity;
    static double dampening; 
};  


#endif //PROJECT_SPRING_H
