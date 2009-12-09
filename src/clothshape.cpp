#include "clothshape.h"

#include "opengl.h"

#include "point.h"
#include "spring.h"
#include "primitives.h"

#include "stdio.h"
#include <math.h>


int ClothShape::getPointWindIndex(int x, int y)
{
    return (y * (res+1) + x);
}

void ClothShape::addNeighbor(Point* p, int x, int y)
{
    if (x < 0 || x > this->res || y < 0 || y > this->res)
        return;

    this->addSpring(p, &this->points[getPointWindIndex(x, y)]);  
}

ClothShape::ClothShape(const Vector3 p, double width, double height, int resolution):
    Shape((resolution+1)*(resolution+1), 2*3*(resolution*2)*(resolution)), res(resolution)
{
    
    Vector3 v1 = p + Vector3(-width / 2, 0, 0);
    Vector3 v2 = p + Vector3(width / 2, -height, 0);
    
    double xseg = (v2.getX() - v1.getX()) / (double)this->res;
    double yseg = (v2.getY() - v1.getY()) / (double)this->res;
  
    fprintf(stderr, "Creating cloth shape.\n");
    int pwind = 0;
    int iwind = 0;
    
    // Create vertices and springs 
    int ycount = 0;
    double y = v1.getY();
    while (ycount <= this->res)
    {
        int xcount = 0;
        double x = v1.getX();
        while (xcount <= this->res)
        {
            
            Vector3 pos = Vector3(x, y, p.getZ());
            
            this->points[pwind] = Point(pos);
                
            // Lock upper corners    
            if ((ycount == 0 && xcount == 0) || (ycount == 0 && xcount == this->res))
            {
                this->points[pwind].lock(true);
            }
            
            for (int ix = -1; ix < 2; ix++)
            {                
                for (int iy = -1; iy < 2; iy++)
                {              
                    if (ix != 0 || iy != 0)
                    {
                        addNeighbor(&this->points[pwind], xcount + ix, ycount + iy);
                    }           
                }  
            }

            // Surface triangles
            if (xcount < this->res && ycount < this->res)
            {
                // upper front triangle
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount);
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1);
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount);

                //lower front triangle
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1);
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount + 1);
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount);    
            }   
            if (xcount > 0 && ycount > 0)
            {
                // upper back triangle
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount);
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount - 1, ycount);                
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount - 1);


                //lower back triangle
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount - 1);
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount - 1, ycount);    
                this->surfaceIndices[iwind++] = getPointWindIndex(xcount - 1, ycount - 1);
                
            }
            
            
            
            pwind++;
            
            xcount++;
            x = v1.getX() + (double)xcount * xseg;
            
        }
        ycount++;
        y = v1.getY() + (double)ycount * yseg;
    }
   
   
    fprintf(stderr, "pwind: %i, pcount: %i\n", pwind, this->pointcount);
    fprintf(stderr, "iwind: %i, icount: %i\n", iwind, this->indexCount);
    
    setupSprings();
    
}
