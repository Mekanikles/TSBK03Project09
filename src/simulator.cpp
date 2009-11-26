#include "simulator.h"

#include "primitives.h"
#include "boxshape.h"

#include "opengl.h"

#include "stdio.h"




Simulator::Simulator(double creationTime)
{
    fprintf(stderr, "Creating simulator.\n");
    BoxShape* box = new BoxShape(Box(Vector3(-2, 1.0, -2), Vector3(2, 5.0, 2)), 3);
    this->shapes.addFirst(box);

    Surface* surface = new Surface(Vector3(-2, 0, -3), Vector3(4, 0, 0), Vector3(0, 0, 6));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(1.5, 0, -3), Vector3(16, 8, 0), Vector3(0, 0, 6));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(-17.5, 8, -3), Vector3(16, -8, 0), Vector3(0, 0, 6));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(-18, 23.5, -3), Vector3(1, -16, 0), Vector3(0, 0, 6));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(17, 7.5, -3), Vector3(1, 16, 0), Vector3(0, 0, 6));
    this->surfaces.addFirst(surface);
    
    this->currentTime = creationTime;
    this->iterations = 0;
}

Simulator::~Simulator()
{

}

void Simulator::tick(double dt)
{
    deltaTime = dt;
    
    double timeStep = deltaTime / 2;
    for (double t = 0; t < deltaTime; t += timeStep)
    {
        this->addGravity();
    
        this->addSpringForces();

        this->applyForces(timeStep);

        this->collidePoints();
        
        this->iterations++;
    }
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

void Simulator::applyForces(double deltaT)
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->applyForces(deltaT);
        node = node->next;
    }    
}

void Simulator::addGravity()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->addAcceleration(Vector3(0,-9.81 * 2, 0));
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
