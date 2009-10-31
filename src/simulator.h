#ifndef PROJECT_SIMULATOR_H
#define PROJECT_SIMULATOR_H

#include "linkedlist.h"
#include "shape.h"

class Simulator
{
public:      

        Simulator();
        ~Simulator();

        void tick();
        void render();
        
protected:
private:
    
    LinkedList<Shape*> shapes;
        
};



#endif //PROJECT_SIMULATOR_H

