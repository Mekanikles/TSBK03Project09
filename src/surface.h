#ifndef PROJECT_SURFACE_H
#define PROJECT_SURFACE_H

#include "primitives.h"

class Surface
{

public:

    Surface(const Vector3& p, const Vector3& v1, const Vector3& v2);

    Vector3 getP() const;
    Vector3 getV1() const;
    Vector3 getV2() const;
    Vector3 getNormal() const;
    
    bool isPointInsideBounds(Vector3 point);
    double signedDistanceToPoint(Vector3 point);

    void render();

protected:
private:

    Vector3 p;
    Vector3 v1;
    Vector3 v2;
    Vector3 normal;
    

};



#endif // PROJECT_SURFACE_H
