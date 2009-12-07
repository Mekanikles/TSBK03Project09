#ifndef PROJECT_BOXSHAPE_H
#define PROJECT_BOXSHAPE_H

#include "primitives.h"
#include "shape.h"

class Point;

class BoxShape : public Shape
{


public:

    BoxShape(const Box& box, int resolution = 1);
    
protected:

    int res;

    int getPointXIndex(int wind);
    int getPointYIndex(int wind);
    int getPointZIndex(int wind);
    int getPointWindIndex(int x, int y, int z);
    
    void addNeighbor(Point* p, int x, int y, int z);

private:

};


#endif // PROJECT_BOXSHAPE_H
