#include "boxshape.h"

#include "opengl.h"

#include "point.h"
#include "spring.h"
#include "primitives.h"

#include "stdio.h"

BoxShape::BoxShape(const Box& box):
    Shape(8, 12)
{
    
    Vector3 v1 = box.getV1();
    Vector3 v2 = box.getV2();
    double xseg = (v2.getX() - v1.getX()) / this->res;
    double yseg = (v2.getY() - v1.getY()) / this->res;
    double zseg = (v2.getZ() - v1.getZ()) / this->res;
  
    fprintf(stderr, "Creating box shape.\n");
    int pwind = 0;
    int swind = 0;
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
                this->points[pwind] = Point(Vector3(x, y, z));
                
                //If not endpoints, connect spring to next vertex
                if (ycount < this->res)
                    this->springs[swind++] = Spring(&this->points[pwind], &this->points[pwind + (this->res + 1) * (this->res + 1) ]);

                if (xcount < this->res)
                    this->springs[swind++] = Spring(&this->points[pwind], &this->points[pwind + this->res + 1]);
                
                if (zcount < this->res)
                    this->springs[swind++] = Spring(&this->points[pwind], &this->points[pwind + 1]);
                   
                //fprintf(stderr, "swind: %i\n", swind);
                pwind++;
                
                zcount++;
                z = zcount * zseg;        
            }
            xcount++;
            x = xcount * xseg;
        }
        ycount++;
        y = ycount * yseg;
    }
    
}
