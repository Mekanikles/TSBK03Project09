#include "boxshape.h"

#include "opengl.h"

#include "point.h"
#include "spring.h"
#include "primitives.h"

#include "stdio.h"
#include <math.h>


int BoxShape::getPointXIndex(int wind)
{
    wind -= (res + 1) * (res + 1) * (wind / ((res + 1)*(res + 1)));
    wind = (wind / (res + 1));
    return wind;
}

int BoxShape::getPointYIndex(int wind)
{
    wind = (wind / ((res + 1)*(res + 1)));
    return wind;
}

int BoxShape::getPointZIndex(int wind)
{
    wind -= (res + 1) * (res + 1) * (wind / ((res + 1)*(res + 1)));
    wind -= (res + 1) * (wind / (res + 1));
    return wind;
}

int BoxShape::getPointWindIndex(int x, int y, int z)
{
    return (y * (res+1) * (res+1) + x * (res+1) + z);
}

void BoxShape::addNeighbor(Point* p, int x, int y, int z)
{
    if (x < 0 || x > this->res || y < 0 || y > this->res || z < 0 || z > this->res)
        return;

    this->addSpring(p, &this->points[getPointWindIndex(x, y, z)]);
    
}

BoxShape::BoxShape(const Box& box, int resolution):
    Shape(ceil(pow(resolution + 1, 3)), 3*(resolution * 2) * (resolution) * 6), res(resolution)
{
    
    Vector3 v1 = box.getV1();
    Vector3 v2 = box.getV2();
    
    Vector3 midpoint = box.getV1() + (box.getV2() - box.getV1()) * 0.5;
    double radius = (box.getV1().getX() - box.getV2().getX()) / 2;
    
    double xseg = (v2.getX() - v1.getX()) / (double)this->res;
    double yseg = (v2.getY() - v1.getY()) / (double)this->res;
    double zseg = (v2.getZ() - v1.getZ()) / (double)this->res;
  
    fprintf(stderr, "Creating box shape.\n");
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
            int zcount = 0;
            double z = v1.getZ();
            while (zcount <= this->res)
            {
                Vector3 pos = Vector3(x, y, z);
                double plen = (pos - midpoint).length();
                Vector3 pnorm = (pos - midpoint); pnorm.normalize();
                //if (plen > radius)
                    //pos = midpoint + pnorm * radius;
                
                this->points[pwind] = Point(pos);
                
                
                for (int ix = -1; ix < 2; ix++)
                {
                    for (int iy = -1; iy < 2; iy++)
                    {
                        for (int iz = -1; iz < 2; iz++)
                        {
                            if (ix != 0 || iy != 0 || iz != 0)
                                addNeighbor(&this->points[pwind], xcount + ix, ycount + iy, zcount + iz);
                        }
                    }
                }
                
                // Surface triangles
                if (xcount < this->res && ycount < this->res && zcount == 0)
                {
                    // upper front triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);

                    // lower front triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount + 1, zcount);                    
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);    
                }   
                if (xcount < this->res && ycount < this->res && zcount == this->res)
                {
                    // upper back triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);

                    // lower back triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);    
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount + 1, zcount);                    
                }    
                if (xcount == this->res && ycount < this->res && zcount < this->res)
                {
                    // upper right triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);

                    // lower right triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount + 1);                    
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);    
                } 
                if (xcount == 0 && ycount < this->res && zcount < this->res)
                {
                    // upper left triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);

                    // lower left triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);    
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount + 1, zcount + 1);                    
                } 
                if (xcount < this->res && ycount == this->res && zcount < this->res)
                {
                    // upper top triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);

                    // lower bottom triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount + 1);                    
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);    
                } 
                if (xcount < this->res && ycount == 0 && zcount < this->res)
                {
                    // upper front triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);

                    // lower front triangle
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount, ycount, zcount + 1);
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount);    
                    this->surfaceIndices[iwind++] = getPointWindIndex(xcount + 1, ycount, zcount + 1);                    
                }  
                
                //fprintf(stderr, "swind: %i\n", swind);
                pwind++;
                
                zcount++;
                z = v1.getZ() + (double)zcount * zseg;        
            }
            xcount++;
            x = v1.getX() + (double)xcount * xseg;
        }
        ycount++;
        y = v1.getY() + (double)ycount * yseg;
    }
   
    fprintf(stderr, "pwind: %i, pcount: %i\n", pwind, pointcount);
    fprintf(stderr, "iwind: %i, icount: %i\n", iwind, this->indexCount);
    
    setupSprings();
    
}
