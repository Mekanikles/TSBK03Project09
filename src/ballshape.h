#ifndef PROJECT_BALLSHAPE_H
#define PROJECT_BALLSHAPE_H

#include "shape.h"

class BallShape : public Shape
{

public:

    BallShape(const Vector3& center, const double radius, int resolution = 1);

protected:

    int res;

    int BallShape::getPointRowIndex(int wind);
    int BallShape::getPointColIndex(int wind);
    int BallShape::getPointLayerIndex(int wind);
    int getPointWindIndex(int row, int col, int layer);    
    void addNeighbor(Point* p, int row, int col, int layer);

private:


};

#endif //PROJECT_BALLSHAPE_H
