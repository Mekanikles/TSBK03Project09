#include "simulator.h"

#include "primitives.h"
#include "boxshape.h"
#include "ballshape.h"
#include "clothshape.h"

#include "opengl.h"

#include "stdio.h"

static double map[10][10] ={{8, 7, 6, 5, 4, 4, 5, 6, 7, 8},
                            {7, 6, 5, 4, 3, 3, 4, 5, 6, 7},
                            {6, 5, 4, 3, 2, 2, 3, 4, 5, 6},
                            {5, 4, 3, 2, 1, 1, 2, 3, 4, 5},
                            {4, 3, 1, 2, 0, 0, 2, 1, 3, 4},
                            {4, 3, 1, 2, 0, 0, 2, 1, 3, 4},
                            {5, 4, 3, 2, 1, 1, 2, 3, 4, 5},
                            {6, 5, 4, 3, 1, 1, 3, 4, 3, 6},
                            {7, 6, 5, 4, 3, 3, 4, 3, 2, 7},
                            {8, 7, 6, 5, 3, 3, 5, 6, 7, 1}};
                                
Simulator::Simulator(double creationTime)
{
    fprintf(stderr, "Creating simulator.\n");
    
    /*
    Surface* surface = new Surface(Vector3(-2, 0, -10), Vector3(4, 0, 0), Vector3(0, 0, 20));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(2, 0, 10), Vector3(-4, 0, 0), Vector3(0, 0, -20));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(1.5, 0, -10), Vector3(16, 8, 0), Vector3(0, 0, 20));
    this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(1.5, 0, 10), Vector3(16, 8, -20), Vector3(16, 8, 0));
    //this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(-17.5, 8, -10), Vector3(16, -8, 0), Vector3(0, 0, 20));
    //this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(-18, 23.5, -10), Vector3(1, -16, 0), Vector3(0, 0, 20));
    //this->surfaces.addFirst(surface);
    
    surface = new Surface(Vector3(17, 7.5, -10), Vector3(1, 16, 0), Vector3(0, 0, 20));
    //this->surfaces.addFirst(surface);
    //this->surfaces.addFirst(surface);
    
    */
    double xs = 10;
    double ys = 4;
    double zs = 10;
    int size = 10;
    Vector3 tl, tr, bl, br;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            tl = Vector3((-size / 2 + i) * xs + xs/2, map[i][j] * ys, (-size / 2 + j) * zs + zs/2);
            tr = Vector3((-size / 2 + i + 1) * xs + xs/2, map[i + 1][j] * ys, (-size / 2 + j) * zs + zs/2);
            bl = Vector3((-size / 2 + i) * xs + xs/2, map[i][j + 1] * ys, (-size / 2 + j + 1) * zs + zs/2);
            br = Vector3((-size / 2 + i + 1) * xs + xs/2, map[i + 1][j + 1] * ys, (-size / 2 + j + 1) * zs + zs/2);
            
            this->surfacemap[i * 2 + j * 10 * 2 + 0] = Surface(tl, tr - tl, bl - tl);
            this->surfacemap[i * 2 + j * 10 * 2 + 1] = Surface(br, bl - br, tr - br);
            
            //Surface* surface = new Surface(Vector3((-size / 2 + i) * xs, 0, (-size / 2 + j) * zs), Vector3(xs, 0, 0), Vector3(0, 0, zs));
            this->surfaces.addFirst(&this->surfacemap[i * 2 + j * 10 * 2 + 0]); 
            //this->surfaces.addFirst(&this->surfacemap[i * 2 + j * 10 * 2 + 1]);
        }
    }
    
    
    
    resetShape(1, 2);
    
    this->currentTime = creationTime;
    this->iterations = 0;
    this->rigidSprings = true;
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

    Vector3 pos = Vector3(0, size * 5, 0);

    switch(id)
    {
        case 1:
        {
            fprintf(stderr, "Creating 1x1 box\n");
            BoxShape* box = new BoxShape(Box(Vector3(-size, -size, -size) + pos, Vector3(size, size, size) + pos), 1);
            this->shapes.addFirst(box); 
            break;        
        }
        case 2:
        {
            fprintf(stderr, "Creating 3x3 box\n");
            BoxShape* box = new BoxShape(Box(Vector3(-size, -size, -size) + pos, Vector3(size, size, size) + pos), 3);
            this->shapes.addFirst(box); 
            break;        
        }
        case 3:
        {
            fprintf(stderr, "Creating 5x5 box\n");
            BoxShape* box = new BoxShape(Box(Vector3(-size, -size, -size) + pos, Vector3(size, size, size) + pos), 5);
            this->shapes.addFirst(box); 
            break;        
        }       
        case 4:
        {
            fprintf(stderr, "Creating low-res ball\n");
            BallShape* ball = new BallShape(Vector3(0, size + 1, 0) + pos, size, 45);
            this->shapes.addFirst(ball);  
            break;
        }    
        case 5:
        {
            fprintf(stderr, "Creating medium-res ball\n");
            BallShape* ball = new BallShape(Vector3(0, size + 1, 0) + pos, size, 30);
            this->shapes.addFirst(ball);  
            break;
        }    
        case 6:
        {
            fprintf(stderr, "Creating high-res ball\n");
            BallShape* ball = new BallShape(Vector3(0, size + 1, 0) + pos, size, 20);
            this->shapes.addFirst(ball);  
            break;
        }    
        case 7:
        {
            fprintf(stderr, "Creating 3x3 cloth\n");
            ClothShape* cloth = new ClothShape(Vector3(0, size*3, 0) + pos, size*3, size*6, 3);
            this->shapes.addFirst(cloth); 
            break;        
        }
        case 8:
        {
            fprintf(stderr, "Creating 7x7 cloth\n");
            ClothShape* cloth = new ClothShape(Vector3(0, size*3, 0) + pos, size*3, size*6, 7);
            this->shapes.addFirst(cloth); 
            break;        
        }
        case 9:
        {
            fprintf(stderr, "Creating 15x15 cloth\n");
            ClothShape* cloth = new ClothShape(Vector3(0, size*3, 0) + pos, size*3, size*6, 15);
            this->shapes.addFirst(cloth); 
            break;        
        }          
         
         
        default:  
        {  
            fprintf(stderr, "Clearing shapes\n");
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

        if (rigidSprings)
        {       
            bool done = false;
            for (int i = 0; i < 40; i++)
            {
                done = this->resolveRigidConstraints();
                this->collidePoints();
                this->iterations++;
                if (done)
                {
                    break;
                }
            }    
        }
        else
        {
            this->collidePoints();
        }
        

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
        node->item->addAcceleration(Vector3(0,-9.81 * 5, 0));
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

bool Simulator::resolveRigidConstraints()
{
    bool retval = true;
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        retval &= node->item->resolveRigidConstraints(deltaTime);
        node = node->next;
    }    
    return retval;
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
    Node<Shape*>* sh = this->shapes.getFirst();
    while (sh != NULL)
    {
        sh->item->collideWithSurfaceMap(surfacemap, deltaTime);
        sh = sh->next;
    }
}

void Simulator::setRigidSprings(bool enable)
{
    this->rigidSprings = enable;
}
