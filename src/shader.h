#ifndef PROJECT_SHADER_H
#define PROJECT_SHADER_H

#include "opengl.h"

class Shader
{
    
public:
    
    Shader(const char* vertFile, const char* fragFile);
    ~Shader();

    void activate();
    void deactivate();

protected:

    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;

private:

    
   

};




#endif //PROJECT_SHADER_H
