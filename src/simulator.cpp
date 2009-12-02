#include "simulator.h"

#include "primitives.h"
#include "boxshape.h"
#include "ballshape.h"

#include "opengl.h"

#include "stdio.h"




Simulator::Simulator(double creationTime)
{
    fprintf(stderr, "Creating simulator.\n");

    Surface* surface = new Surface(Vector3(-2, 0, -10), Vector3(4, 0, 0), Vector3(0, 0, 20));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(1.5, 0, -10), Vector3(16, 8, 0), Vector3(0, 0, 20));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(-17.5, 8, -10), Vector3(16, -8, 0), Vector3(0, 0, 20));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(-18, 23.5, -10), Vector3(1, -16, 0), Vector3(0, 0, 20));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(17, 7.5, -10), Vector3(1, 16, 0), Vector3(0, 0, 20));
    this->surfaces.addFirst(surface);
    
    resetShape(1, 2);
    
    this->currentTime = creationTime;
    this->iterations = 0;
}

Simulator::~Simulator()
{

}

void Simulator::resetShape(int id, double size)
{

    Node<Shape*>* node = this->shapes.getFirst();
    if (node)
    {
        delete node->item;
        this->shapes.remove(node);   
    }

    switch(id)
    {
        case 1:
        {
            fprintf(stderr, "Creating 1x1 box\n");
            BoxShape* box = new BoxShape(Box(Vector3(-size, size, -size), Vector3(size, size*3, size)), 1);
            this->shapes.addFirst(box); 
            break;        
        }
        case 2:
        {
            fprintf(stderr, "Creating 3x3 box\n");
            BoxShape* box = new BoxShape(Box(Vector3(-size, size, -size), Vector3(size, size*3, size)), 3);
            this->shapes.addFirst(box); 
            break;        
        }
        case 3:
        {
            fprintf(stderr, "Creating 5x5 box\n");
            BoxShape* box = new BoxShape(Box(Vector3(-size, size, -size), Vector3(size, size*3, size)), 5);
            this->shapes.addFirst(box); 
            break;        
        }       
        case 4:
        {
            fprintf(stderr, "Creating low-res ball\n");
            BallShape* ball = new BallShape(Vector3(0, size*2 + 1, 0), size, 45);
            this->shapes.addFirst(ball);  
            break;
        }    
        case 5:
        {
            fprintf(stderr, "Creating medium-res ball\n");
            BallShape* ball = new BallShape(Vector3(0, size*2 + 1, 0), size, 30);
            this->shapes.addFirst(ball);  
            break;
        }    
        case 6:
        {
            fprintf(stderr, "Creating high-res ball\n");
            BallShape* ball = new BallShape(Vector3(0, size*2 + 1, 0), size, 20);
            this->shapes.addFirst(ball);  
            break;
        }    
         
        default:  
        {  
            fprintf(stderr, "Creating 1x1 box\n");
            BoxShape* box = new BoxShape(Box(Vector3(-2, size, -2), Vector3(2, size*2, 2)), 1);
            this->shapes.addFirst(box); 
            break;
        }
    };
}

void Simulator::tick(double dt)
{
    deltaTime = dt;
    
    double timeStep = deltaTime / 4;
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
        node->item->addSpringForces(deltaTime);
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
