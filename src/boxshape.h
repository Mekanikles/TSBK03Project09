#ifndef PROJECT_BOXSHAPE_H
#define PROJECT_BOXSHAPE_H

#include "primitives.h"
#include "shape.h"


class BoxShape : public Shape
{


public:

    BoxShape(const Box& box);

protected:

    static const int res = 2;

private:

};


#endif // PROJECT_BOXSHAPE_H
