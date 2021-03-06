#include "stdio.h"

#include "platform.h"
#include "simulator.h"
#include "renderer.h"
#include "surface.h"
#include "spring.h"

#include "opengl.h"

#include "math.h"

Platform* platform;

const int screenwidth = 640;
const int screenheight = 480;

const double targetFps = 30;
const double frameLength = 1.0/30;

Simulator* sim;
Renderer* renderer;

// Handles all input to the simulator
void handleInput()
{
    static double size = 2;

    // Get viewing relative movement
    double mrelx = platform->getMouseRelX();
    double mrely = platform->getMouseRelY();

    // Get position relative movement
    double relx = -platform->getChar('A') + platform->getChar('D');
    double relz = -platform->getChar('W') + platform->getChar('S');
    double rely = -platform->getChar('Q') + platform->getChar('E');
    
    // If the left mousebutton is pressed, mouse movement applies a horizontal force to the simulation orthogonal to the camera eye vector
    if (platform->getMouseButton(0))
    {
        Vector3 v = Vector3(mrelx, 0, mrely);
        double angle  = -renderer->getCameraTurnAngle() * M_PI/180;
        Vector3 rotv = Vector3(cos(angle) * v.getX() + sin(angle) * v.getZ(), v.getY(), -sin(angle) * v.getX() + cos(angle) * v.getZ());
        
        sim->attract(rotv, 10);
    }
    // The right mousebutton applies a vertical force
    if (platform->getMouseButton(1))
    {
        Vector3 v = Vector3(0, -mrely, 0);   
        sim->attract(v, 10);
    }
    
    // If no button is pressed, mouse movement controls viewing
    if (!platform->getMouseButton(0) && !platform->getMouseButton(1))
    {
        if (mrelx)
            renderer->turnCamera(mrelx);
            
        if (mrely)
            renderer->tiltCamera(mrely);
    }
    
    // Move camera position
    if (relx || rely || relz)
        renderer->moveCamera(Vector3(relx/2, rely/2, relz/2));
    
    // Changing shape size
    if (platform->getChar('T'))
    {
        size+=10*frameLength;
        if (size > 10.0)
            size = 10.0;
            
        fprintf(stderr, "Shape size: %f\n", size);    
    }
    else if (platform->getChar('R'))
    {
        size-=10*frameLength;
        if (size < 1.0)
            size = 0.5;
            
        fprintf(stderr, "Shape size: %f\n", size);    
    }

    // Changing surface friction
    if (platform->getChar('G'))
    {
        double f = Surface::getFriction();
        f += 1*frameLength;
        if (f > 1.0)
            f = 1.0;
        Surface::setFriction(f);
    
        fprintf(stderr, "Surface friction: %f\n", f);    
    }
    else if (platform->getChar('F'))
    {
        double f = Surface::getFriction();
        f -= 1*frameLength;
        if (f < 0.0)
            f = 0.0;
        Surface::setFriction(f);
    
        fprintf(stderr, "Surface friction: %f\n", f);    
    }

    // Changing spring constant
    if (platform->getChar('U'))
    {
        double e = Spring::getElasticity();
        e += 1000*frameLength;
        if (e > 3000)
            e = 3000;
        Spring::setElasticity(e);
    
        fprintf(stderr, "Spring constant: %f\n", e);    
    }
    else if (platform->getChar('Y'))
    {
        double e = Spring::getElasticity();
        e -= 1000*frameLength;
        if (e < 10)
            e = 10;
        Spring::setElasticity(e);
    
        fprintf(stderr, "Spring constant: %f\n", e);    
    }    
    
    // Changing spring dampening
    if (platform->getChar('J'))
    {
        double d = Spring::getDampening();
        d += 100*frameLength;
        if (d > 500)
            d = 500;
        Spring::setDampening(d);
    
        fprintf(stderr, "Spring dampening: %f\n", d);    
    }
    else if (platform->getChar('H'))
    {
        double d = Spring::getDampening();
        d -= 100*frameLength;
        if (d < 0)
            d = 0;
        Spring::setDampening(d);
    
        fprintf(stderr, "Spring dampening: %f\n", d);    
    }    
    
    // Changing spring maxlength
    if (platform->getChar('O'))
    {
        double l = Spring::getMaxlength();
        l += 1*frameLength;
        if (l > 1.5)
            l = 1.5;
        Spring::setMaxlength(l);
    
        fprintf(stderr, "Spring maxlength: %f\n", l);
    }
    else if (platform->getChar('I'))
    {
        double l = Spring::getMaxlength();
        l -= 1*frameLength;
        if (l < 1)
            l = 1;
        Spring::setMaxlength(l);
    
        fprintf(stderr, "Spring maxlength: %f\n", l);
    }    
    
    // Changing spring minlength
    if (platform->getChar('L'))
    {
        double l = Spring::getMinlength();
        l += 1*frameLength;
        if (l > 1)
            l = 1;
        Spring::setMinlength(l);
    
        fprintf(stderr, "Spring minlength: %f\n", l);
    }
    else if (platform->getChar('K'))
    {
        double l = Spring::getMinlength();
        l -= 1*frameLength;
        if (l < 0.5)
            l = 0.5;
        Spring::setMinlength(l);
    
        fprintf(stderr, "Spring minlength: %f\n", l);
    }    
            
    // Toggle using rigid springs
    if (platform->getChar('C'))
    {
        sim->setRigidSprings(true);
        fprintf(stderr, "Rigid springs enabled\n");
    }
    else if (platform->getChar('X'))
    {
        sim->setRigidSprings(false);
        fprintf(stderr, "Rigid springs disabled\n");
    }      

    // Toggle using wireframes
    if (platform->getChar('P'))
    {
        renderer->setWireframe(true);
        fprintf(stderr, "Wireframe enabled\n");
    }
    else if (platform->getChar('�'))
    {
        renderer->setWireframe(false);
        fprintf(stderr, "Wireframe disabled\n");
    }      

    // Get states of numerical keys
    // Keys 1-9 create different shapes, key 0 removes current shape
    int digitkey;
    for (digitkey = 0; digitkey < 10; digitkey++)
    {
        if (platform->getChar('0' + (char)digitkey))
        {
            break;
        }
    }
    if (digitkey < 10)
    {
        sim->resetShape(digitkey, size);
    }

}

// Main loop, runs every frame
void mainloop(double dt)
{
    sim->tick(dt);
    handleInput();
    renderer->render(sim);
}

// Initialize everything
void init()
{
    // Initialize platform layer
    platform = Platform::getInstance();
    platform->initialize(640, 480, false);
    
    sim = new Simulator();
    renderer = new Renderer();   
}

// Program entry
int main()
{
    fprintf(stderr, "Project start!\n");
    fprintf(stderr, "Use digits 1-9 to create shapes!\n");
    fprintf(stderr, "Use keys X and C to toggle usage of rigid constraints\n");

    init();

    double t = platform->getTime();
    double lastFpsCheck = platform->getTime();
    double nextFrame = t;
    int fps = 0;
    while (platform->isRunning())
    {
        platform->update();
        t = platform->getTime();
            
        if (t >= nextFrame)    
        {
            nextFrame += frameLength;
            mainloop(frameLength);

            fps++;
            if (t - lastFpsCheck > 1.0)
            {
                fprintf(stderr, "FPS: %i\n", fps);
                lastFpsCheck = t;
                fps = 0;
                fprintf(stderr, "Iterations: %i\n", sim->iterations);
                sim->iterations = 0;
            }
                   
            platform->refreshWindow();
        }
        t = platform->getTime();
        //platform->sleep(nextFrame - t);
    }

    delete renderer;
    delete sim;
    
    
    platform->terminate();
    
    return 0;
}

