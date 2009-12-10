#include "shader.h"

#include "stdlib.h"
#include "stdio.h"


static char* textFileRead(const char *fn) {


        FILE *fp;
        char *content = NULL;

        int f, count;
		
        fp = fopen(fn, "r");
        if (!fp)
        {
            fprintf(stderr, "Could not find file %s\n", fn);
            fclose(fp);
            return NULL;
        }

        fseek(fp, 0, SEEK_END);
        count = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        
        if (count > 0) {
            content = (char *)malloc(sizeof(char) * (count+1));
            count = fread(content, sizeof(char), count, fp);
            content[count] = '\0';
        }
        else
        {
            return NULL;
            fclose(fp);
        }
        
        fclose(fp);

        return content;
}

static void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        fprintf(stderr, "%s\n",infoLog);
        free(infoLog);
    }
}

static void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        fprintf(stderr, "%s\n",infoLog);
        free(infoLog);
    }
}
 
 
 
Shader::Shader(const char* vertFile, const char* fragFile)
{
    char* vs = NULL;
    char* fs = NULL;

    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	

    vs = textFileRead(vertFile);
    fs = textFileRead(fragFile);

    if (vs != NULL)
    {
        const char* vv = vs;
        glShaderSource(this->vertexShader, 1, &vv,NULL);
        free(vs);    
        glCompileShader(this->vertexShader);
    
    }

    if (fs != NULL)
    {
        const char* ff = fs;
        glShaderSource(this->fragmentShader, 1, &ff,NULL);
        free(fs);
        glCompileShader(this->fragmentShader);
    }
    
    this->program = glCreateProgram();
    
    glAttachShader(this->program, this->vertexShader);
    glAttachShader(this->program, this->fragmentShader);

    glLinkProgram(this->program);
    
    printShaderInfoLog(this->vertexShader);
    printShaderInfoLog(this->fragmentShader);
    printProgramInfoLog(this->program);
    
}

Shader::~Shader()
{
    glDetachShader(this->program, this->vertexShader);
    glDetachShader(this->program, this->fragmentShader);
    
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    
    glDeleteProgram(this->program); 
}


void Shader::activate()
{
    glUseProgram(this->program);
}

void Shader::deactivate()
{
    glUseProgram(0);
}
