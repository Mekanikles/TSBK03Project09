#include "stdio.h"

#include "platform.h"
#include "simulator.h"
#include "renderer.h"

#include "opengl.h"

Platform* platform;

const int screenwidth = 640;
const int screenheight = 480;

const double targetFps = 60;

Simulator* sim;
Renderer* renderer;


void handleCamera()
{
    double mrelx = platform->getMouseRelX();
    double mrely = platform->getMouseRelY();

    double relx = -platform->getChar('A') + platform->getChar('D');
    double relz = -platform->getChar('W') + platform->getChar('S');
    double rely = -platform->getChar('Q') + platform->getChar('E');
    
    if (platform->getMouseButton(0))
    {
        sim->attract(Vector3(mrelx, -mrely, 0), 10);
    }
    else
    {
        if (mrelx)
            renderer->turnCamera(mrelx);
            
        if (mrely)
            renderer->tiltCamera(mrely);

        if (relx || rely || relz)
            renderer->moveCamera(Vector3(relx/2, rely/2, relz/2));
    }
    
}


void mainloop(double dt)
{
    sim->tick(dt);
    handleCamera();
    renderer->render(sim);
}


void init()
{
    sim = new Simulator(platform->getTime());
    renderer = new Renderer();   
}

int main()
{
    fprintf(stderr, "Project start!\n");
  
    platform = Platform::getInstance();
  
    platform->initialize(640, 480, false);
 
    init();

    double t = platform->getTime();
    double lastFpsCheck = platform->getTime();
    double nextFrame = t;
    double frameLength = 1.0/targetFps;
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
        platform->sleep(nextFrame - t);
    }

    delete renderer;
    delete sim;
    
    
    platform->terminate();
    
    return 0;
}

