#include "simulator.h"

#include "primitives.h"
#include "boxshape.h"


#include "stdio.h"

Simulator::Simulator()
{
    fprintf(stderr, "Creating simulator.\n");
    BoxShape* box = new BoxShape(Box(Vector3(-0.5, -0.5, -0.5), Vector3(0.5, 0.5, 0.5)));
    this->shapes.addFirst(box);
}

Simulator::~Simulator()
{

}

void Simulator::tick()
{

}

void Simulator::render()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->render();
        node = node->next;
    }
    
}
