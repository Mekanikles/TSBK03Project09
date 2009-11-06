#ifndef PROJECT_PLATFORM_H
#define PROJECT_PLATFORM_H

class Platform
{

    static Platform* instance;

public:

    static Platform* getInstance();

    
    bool initialize(int windowWidth, int windowHeight, bool fullscreen);
    void terminate();
        
    void update();
    void refreshWindow();
    void sleep(double seconds);
    
    int getChar(unsigned char c);
    int getMousePosX();
    int getMousePosY();
    int getMouseRelX();
    int getMouseRelY();
    int getMouseButton(unsigned int button);
    double getTime();
    bool isRunning();

private:

    int windowWidth;
    int windowHeight;
    
    int mousex;
    int mousey;
    int old_mousex;
    int old_mousey;
    int rel_mousex;
    int rel_mousey;
    
    
    bool initialized;
    bool running;
};



#endif // PROJECT_PLATFORM_H

