#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H

#include "primitives.h"

class Point
{


public:
    Point(const Vector3& pos, double mass = 1.0);
    Point();
    
    Vector3 getPos();
    
protected:

    Vector3 pos;
    double mass;
    
private:


};



#endif //PROJECT_POINT_H
