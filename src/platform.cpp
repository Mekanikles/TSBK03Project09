#include "platform.h"

#include "stdlib.h"
#include "stdio.h"

#include "opengl.h"


Platform* Platform::instance = NULL;


Platform* Platform::getInstance()
{
    if (Platform::instance == NULL)
    {
        Platform::instance = new Platform();
    }
    return Platform::instance;
}


bool Platform::initialize(int windowWidth, int windowHeight, bool fullscreen)
{
    if (!glfwInit())
    {
        return false;
    }
    
    if (!glfwInit())
    {
        fprintf(stderr, "Could not initialize glfw!\n");
        return false;
    }

    if (!glfwOpenWindow(windowWidth, windowHeight, 0, 0, 0, 0, 0, 0, fullscreen? GLFW_FULLSCREEN : GLFW_WINDOW))
    {
        fprintf(stderr, "Could not open glfw window!\n");
        return false;
    }

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    glClearColor(0.0, 0.0, 0.0, 0.8);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
	glClearDepth(1.0f);							// Depth Buffer Setup
	glDepthFunc (GL_LESS);	    							// The Type Of Depth Testing To Do
	
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);	// Use The Good Calculations
    glEnable (GL_LINE_SMOOTH);
    
    #ifdef WIN32
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
          // Problem: glewInit failed, something is seriously wrong.
          fprintf(stderr, "Glew initialization error: %s\n", glewGetErrorString(err));
          return false;
        }
        fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));  

		if (glewIsSupported("GL_VERSION_2_0"))
        {
			printf("Ready for OpenGL 2.0\n");
        }
		else 
        {
			printf("OpenGL 2.0 not supported\n");
			return false;
		}      
    #endif   
        

    this->initialized = true;
    this->running = true;

    glfwPollEvents();
    glfwGetMousePos(&this->mousex, &this->mousey);
    this->old_mousex = this->mousex;
    this->old_mousey = this->mousey;
    
    return true;
}

void Platform::terminate()
{

    glfwTerminate();
}


void Platform::update()
{
    glfwPollEvents();

    if(glfwGetKey(GLFW_KEY_ESC) )
    {
        running = false;
    }
    
    glfwGetMousePos(&this->mousex, &this->mousey);
    this->rel_mousex += this->mousex - this->old_mousex;
    this->rel_mousey += this->mousey - this->old_mousey;
    glfwSetMousePos(this->windowWidth/2, this->windowHeight/2);
    glfwGetMousePos(&this->old_mousex, &this->old_mousey);
}

void Platform::refreshWindow()
{
    glfwSwapBuffers();
}

void Platform::sleep(double seconds)
{
    glfwSleep(seconds);
}

int Platform::getChar(unsigned char c)
{
    return glfwGetKey(c);
}

int Platform::getMousePosX()
{
    return this->mousex;
}

int Platform::getMousePosY()
{
    return this->mousey;
}

int Platform::getMouseRelX()
{
    int ret = this->rel_mousex;
    this->rel_mousex = 0;
    return ret;
}

int Platform::getMouseRelY()
{
    int ret = this->rel_mousey;
    this->rel_mousey = 0;
    return ret;
}

int Platform::getMouseButton(unsigned int button)
{
    return glfwGetMouseButton(button);
}

double Platform::getTime()
{
    return glfwGetTime();
}

bool Platform::isRunning()
{
    return this->running;
}