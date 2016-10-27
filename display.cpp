#include "display.h"

/****************************************************************************************************************************************************************/
display::display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);

    GLenum status = glewInit();
    if(status != GLEW_OK)
        std::cerr << "\n\nGlew failed to initialise!!\n\n";

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    isRunning = true;
}
/****************************************************************************************************************************************************************/

display::~display()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
/****************************************************************************************************************************************************************/

bool display::Running(){
    return isRunning;
}
/****************************************************************************************************************************/

void display::setFill(float r, float g, float b, float a){
    GLfloat color[] = {r,g,b,a};
    glClearBufferfv(GL_COLOR, 0, color);
    glClear(GL_DEPTH_BUFFER_BIT);
}
/****************************************************************************************************************************/

void display::Update(){
    SDL_GL_SwapWindow(window);

    SDL_Event e;

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            isRunning = false;
        }
    }
}
/****************************************************************************************************************************************************************/
