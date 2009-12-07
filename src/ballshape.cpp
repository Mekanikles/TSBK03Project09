#include "ballshape.h"

#include "opengl.h"

#include "point.h"
#include "spring.h"
#include "primitives.h"

#include "stdio.h"
#include <math.h>

int BallShape::getPointRowIndex(int wind)
{
    return 0;
}

int BallShape::getPointColIndex(int wind)
{
    return 0;
}

int BallShape::getPointLayerIndex(int wind)
{
    return 0;
}

int BallShape::getPointWindIndex(int row, int col, int layer)
{
    return 3 + row + ((180 / this->res) -1) * col;
}

void BallShape::addNeighbor(Point* p, int row, int col, int layer)
{
    //fprintf(stderr, "Row: %i, col: %i, 180/this->res: %i\n", row, col, (180 / this->res));
    if (row < 0 || row >= (180 / this->res) - 1 || layer < 0 || layer > this->res)
        return;

    if (col < 0)
        col = col + (360 / this->res);
        
    if (col >= (360 / this->res))
        col = col - (360 / this->res);
            
    this->addSpring(p, &this->points[getPointWindIndex(row, col, layer)]);
}

BallShape::BallShape(const Vector3& center, const double radius, int resolution):
    Shape(3 + (360 / resolution) * ((180 / resolution)-1)), res(resolution)
{
    fprintf(stderr, "Creating box shape.\n");
    int pwind = 0;

    // center vertex
    this->points[0] = Point(center);

    // near end
    this->points[1] = Point(center + Vector3(0, 0, radius));
    this->addSpring(&this->points[0], &this->points[1]);
    
    // far end
    this->points[2] = Point(center + Vector3(0, 0, -radius));
    this->addSpring(&this->points[0], &this->points[2]);   
    
    double i;
    double j;
    pwind = 3;
    
    Vector3 midpoint = Vector3(center.getX(), center.getY(), center.getZ());
    
    int col = 0;
    for(i = 0; i < 360; i+=res)
    {
        int row = 0;
        
        for(j = res; j <= 180 - res; j+=res)
        {
            double a = i/180*M_PI;
            double b = j/180*M_PI;  
            
            this->points[pwind] = Point(Vector3(radius * sin(a) * sin(b), 
                                                radius * cos(a) * sin(b),
                                                radius * cos(b)) + midpoint);
            // Connect to center vertex
            this->addSpring(&this->points[0], &this->points[pwind]);
            
            addNeighbor(&this->points[pwind], row - 1, col - 1, 0);
            addNeighbor(&this->points[pwind], row, col - 1, 0);
            addNeighbor(&this->points[pwind], row + 1, col - 1, 0);
            
            addNeighbor(&this->points[pwind], row - 1, col, 0);
            addNeighbor(&this->points[pwind], row + 1, col, 0);
            
            addNeighbor(&this->points[pwind], row - 1, col + 1, 0);
            addNeighbor(&this->points[pwind], row, col + 1, 0);
            addNeighbor(&this->points[pwind], row + 1, col + 1, 0);
            
            pwind++;
            
            row++;
        }
        // Bind to near vertex
        this->addSpring(&this->points[1], &this->points[pwind - (180/res) + 1]);
        
        // Bind to far vertex
        this->addSpring(&this->points[2], &this->points[pwind-1]);
        
        col++;
    }
    
    fprintf(stderr, "pwind: %i, pcount: %i\n", pwind, pointcount);  
  
    setupSprings();

}
