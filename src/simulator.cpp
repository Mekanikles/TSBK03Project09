#include "simulator.h"

#include "primitives.h"
#include "boxshape.h"

#include "opengl.h"

#include "stdio.h"




Simulator::Simulator(double creationTime)
{
    fprintf(stderr, "Creating simulator.\n");
    BoxShape* box = new BoxShape(Box(Vector3(-0.5, 1.5, -0.5), Vector3(0.5, 2, 0.5)));
    this->shapes.addFirst(box);

    Surface* surface = new Surface(Vector3(-2, 0, -2), Vector3(4, 0, 0), Vector3(0, 0, 4));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(1.5, 0, -2), Vector3(4, 2, 0), Vector3(0, 0, 4));
    this->surfaces.addFirst(surface);
    
    
    this->currentTime = creationTime;
}

Simulator::~Simulator()
{

}

void Simulator::tick(double time)
{
    deltaTime = time - currentTime;
    currentTime = time;

    this->addGravity();
    
    this->addSpringForces();

    this->applyForces();

    this->collidePoints();
}

void Simulator::renderShapes()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->render();
        node = node->next;
    }
}

void Simulator::renderSurfaces()
{
    Node<Surface*>* s = this->surfaces.getFirst();
    while (s != NULL)
    {
        s->item->render();
        s=s->next;
    }            
}

void Simulator::applyForces()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->applyForces(deltaTime);
        node = node->next;
    }    
}

void Simulator::addGravity()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->addAcceleration(Vector3(0,-9.81, 0));
        node = node->next;
    }    
}

void Simulator::attract(Vector3 pos, double strength)
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->addAcceleration(pos * strength);
        node = node->next;
    }
}

void Simulator::addSpringForces()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->addSpringForces();
        node = node->next;
    }    

}

void Simulator::collidePoints()
{
    Node<Surface*>* s = this->surfaces.getFirst();
    while (s != NULL)
    {
        Node<Shape*>* sh = this->shapes.getFirst();
        while (sh != NULL)
        {
            sh->item->collideWithSurface(s->item, deltaTime);
            sh = sh->next;
        }   
        s=s->next;
    }    
}
