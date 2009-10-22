
#include "stdio.h"
#include "GL/glfw.h"
#include "GL/glext.h"

const int screenwidth = 640;
const int screenheight = 480;

int main()
{

  fprintf(stderr, "Project test!\n");

  if (!glfwInit())
  {
      fprintf(stderr, "Could not initialize glfw!\n");
      return 1;
  }

  if (!glfwOpenWindow(screenwidth, screenheight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
  {
      fprintf(stderr, "Could not open glfw window!\n");
      return 1;
  }
  
  double t = glfwGetTime();
  double lastFpsCheck = glfwGetTime();
  int fps = 0;
  while (!glfwGetKey(GLFW_KEY_ESC))
  {
      t = glfwGetTime();
      

      
      fps++;
      if (t - lastFpsCheck > 1.0)
      {
          fprintf(stderr, "FPS: %i\n", fps);
          lastFpsCheck = t;
          fps = 0;
      }
      
      glfwSwapBuffers();
      glfwSleep(0.03);
  }
     
  glfwTerminate();
  

  return 0;
}

