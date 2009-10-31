#include "ballshape.h"

#include <math.h>


BallShape::BallShape(double radius):
    Shape(20, 20), radius(radius)
{
    int i;
    int j;
    
    fprintf(stderr, "Creating box shape.\n");
    
    for (i = 0; i < this->cols; i++)
    {
        for (j = 0; j < this->rows; j++)
        {
            //rc = (i * 2 * M_PI/this->cols);
            //rr = (i * M_PI/this->rows);
            //Point p = new Point( (i * M_PI/2)
    
        }
    }
       
}
