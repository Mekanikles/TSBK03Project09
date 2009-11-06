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
    
    void addForces();
    void calcInertialLength();
    
protected:
private:
    
    Point* p1;
    Point* p2;
    double elasticity;
    double length;
};  


#endif //PROJECT_SPRING_H
