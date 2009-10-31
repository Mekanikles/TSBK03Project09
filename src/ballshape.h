#ifndef PROJECT_BALLSHAPE_H
#define PROJECT_BALLSHAPE_H

#include "shape.h"

class BallShape : public Shape
{

public:

    BallShape(double radius);

protected:

    static const int rows = 4;
    static const int cols = 4;
    double radius;

private:



};

#endif //PROJECT_BALLSHAPE_H
