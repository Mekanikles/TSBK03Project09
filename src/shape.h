#ifndef PROJECT_SHAPE_H
#define PROJECT_SHAPE_H

#include "linkedlist.h"

class Point;
class Spring;

class Shape
{
    public:
    
        int pointcount;
        int springcount;
        
        virtual void render();

    protected:
    
        Shape(int pointcount, int springcount);
        virtual ~Shape();
        
        Point* points;
        Spring* springs;
        
    private:    
};


#endif //PROJECT_SHAPE_H
