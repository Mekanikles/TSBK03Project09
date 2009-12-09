#ifndef PROJECT_CLOTHSHAPE_H
#define PROJECT_CLOTHSHAPE_H

#include "primitives.h"
#include "shape.h"

class Point;

class ClothShape : public Shape
{

public:

    ClothShape(const Vector3 p, double width, double height, int resolution = 1);

protected:

    int res;

    int getPointWindIndex(int x, int y);
    void addNeighbor(Point* p, int x, int y);

private:

};


#endif // PROJECT_CLOTHSHAPE_H
