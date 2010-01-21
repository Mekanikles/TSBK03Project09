#include "simulator.h"

#include "primitives.h"
#include "boxshape.h"
#include "ballshape.h"
#include "clothshape.h"

#include "opengl.h"

#include "stdio.h"

// Height map used to build world
static double map[10][10] ={{8, 7, 6, 5, 7, 7, 5, 6, 7, 8},
                            {7, 2, 5, 4, 3, 3, 4, 5, 6, 7},
                            {6, 5, 4, 5, 3, 3, 5, 4, 5, 6},
                            {5, 4, 3, 2, 1, 1, 2, 3, 4, 5},
                            {7, 3, 2, 1, 0, 0, 1, 2, 3, 7},
                            {7, 3, 2, 1, 0, 0, 1, 2, 3, 7},
                            {5, 4, 3, 2, 1, 1, 2, 3, 4, 5},
                            {6, 5, 4, 3, 1, 1, 3, 4, 3, 6},
                            {7, 6, 5, 4, 3, 3, 4, 3, 2, 7},
                            {8, 7, 6, 5, 3, 3, 5, 6, 7, 8}};
                                
Simulator::Simulator()
{
    fprintf(stderr, "Creating simulator.\n");
    
    // Translate height map to surface polygons
    // Map dimensions are currently hardcoded
    double xs = 10;
    double ys = 4;
    double zs = 10;
    int size = 10;
    Vector3 tl, tr, bl, br;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            // Calculate the world coordinates of surface from map
            tl = Vector3((-size / 2 + i) * xs + xs/2, map[i][j] * ys, (-size / 2 + j) * zs + zs/2);
            tr = Vector3((-size / 2 + i + 1) * xs + xs/2, map[i + 1][j] * ys, (-size / 2 + j) * zs + zs/2);
            bl = Vector3((-size / 2 + i) * xs + xs/2, map[i][j + 1] * ys, (-size / 2 + j + 1) * zs + zs/2);
            br = Vector3((-size / 2 + i + 1) * xs + xs/2, map[i + 1][j + 1] * ys, (-size / 2 + j + 1) * zs + zs/2);
            
            // Add surfaces to surface lookup
            this->surfacemap[i * 2 + j * 10 * 2 + 0] = Surface(tl, tr - tl, bl - tl);
            this->surfacemap[i * 2 + j * 10 * 2 + 1] = Surface(br, bl - br, tr - br);
            
            // Add surfaces to surface list
            this->surfaces.addFirst(&this->surfacemap[i * 2 + j * 10 * 2 + 0]); 
            this->surfaces.addFirst(&this->surfacemap[i * 2 + j * 10 * 2 + 1]);
        }
    }
    
    this->iterations = 0;
    this->rigidSprings = true;
}

Simulator::~Simulator()
{

}

// Remove current shape and create a new shape from id
void Simulator::resetShape(int id, double size)
{

    // Remove shapes
    Node<Shape*>* node = this->shapes.getFirst();
    if (node)
    {
        delete node->item;
        this->shapes.remove(node);   
    }

    // Position of shape
    Vector3 pos = Vector3(0, size * 4, 0);

    // Create new shape
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
            ClothShape* cloth = new ClothShape(Vector3(0, size*3, 0) + pos * 1.5, size*3, size*6, 3);
            this->shapes.addFirst(cloth); 
            break;        
        }
        case 8:
        {
            fprintf(stderr, "Creating 7x7 cloth\n");
            ClothShape* cloth = new ClothShape(Vector3(0, size*3, 0) + pos * 1.5, size*3, size*6, 7);
            this->shapes.addFirst(cloth); 
            break;        
        }
        case 9:
        {
            fprintf(stderr, "Creating 15x15 cloth\n");
            ClothShape* cloth = new ClothShape(Vector3(0, size*3, 0) + pos * 1.5, size*3, size*6, 15);
            this->shapes.addFirst(cloth); 
            break;        
        }
        default:  
        {  
            fprintf(stderr, "Clearing shapes\n");
            break;
        }
    }
}

// One frame of simulation
void Simulator::tick(double dt)
{
    deltaTime = dt;
    
    // Do 4 physicsteps for each frame
    double timeStep = deltaTime / 4;
    for (double t = 0; t < deltaTime; t += timeStep)
    {        
        this->addGravity();
        
        this->addSpringForces();

        this->applyForces(timeStep);

        // If rigid constraints are used, make sure the system is "balanced"
        // before continuing
        if (rigidSprings)
        {       
            bool done = false;
            // Iterate constraints and collision response until changes are small enough
            // Use a maximum of 40 iterations
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

// Render function for all shapes
void Simulator::renderShapes(bool wireframe)
{
    if (!wireframe)
    {
        Node<Shape*>* node = this->shapes.getFirst();
        while (node != NULL)
        {
            node->item->render();
            node = node->next;
        }
    }
    else
    {
        Node<Shape*>* node = this->shapes.getFirst();
        while (node != NULL)
        {
            node->item->renderWireframe();
            node = node->next;
        }    
    }
}

// Render function for all surfaces
void Simulator::renderSurfaces(bool wireframe)
{
    if (!wireframe)
    {
        Node<Surface*>* s = this->surfaces.getFirst();
        while (s != NULL)
        {
            s->item->render();
            s=s->next;
        }            
    }
    else
    {
        Node<Surface*>* s = this->surfaces.getFirst();
        while (s != NULL)
        {
            s->item->renderWireframe();
            s=s->next;
        }            
    }
}

// Apply all accumulated forces on all points
void Simulator::applyForces(double deltaT)
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->applyForces(deltaT);
        node = node->next;
    }    
}

// Apply a constant gravitational force to all points
void Simulator::addGravity()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        // Gravity is enhanced to give a better feel
        node->item->addAcceleration(Vector3(0,-9.81 * 5, 0));
        node = node->next;
    }    
}

// Apply a force to all points
void Simulator::attract(Vector3 pos, double strength)
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->addAcceleration(pos * strength);
        node = node->next;
    }
}

// Make sure all rigid constraints are satisfied
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

// Add all spring-related forces
void Simulator::addSpringForces()
{
    Node<Shape*>* node = this->shapes.getFirst();
    while (node != NULL)
    {
        node->item->addSpringForces(deltaTime);
        node = node->next;
    }    

}

// Collision detection and response between shapes and surfaces
void Simulator::collidePoints()
{
    Node<Shape*>* sh = this->shapes.getFirst();
    while (sh != NULL)
    {
        sh->item->collideWithSurfaceMap(surfacemap, deltaTime);
        sh = sh->next;
    }
}

// Toggle usage of rigid constraints
void Simulator::setRigidSprings(bool enable)
{
    this->rigidSprings = enable;
}
