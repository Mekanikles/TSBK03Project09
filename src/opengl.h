#ifndef PROJECT_OPENGL_H
#define PROJECT_OPENGL_H

// All includes needed for opengl operations
#ifndef WIN32
    #include "GL/glext.h"
#else
    #include "GL/glew.h"
#endif    

#include "GL/glfw.h"

#include "GL/gl.h"
#include "GL/glu.h"

#endif //PROJECT_OPENGL_H
