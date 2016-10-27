#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

class display
{
    public:

        display(int width, int height, const std::string& title);

        bool Running();
        void setFill(float r, float g, float b, float a);
        void Update();

        virtual ~display();

    private:

        SDL_Window* window;
        SDL_GLContext glContext;

        bool isRunning;

};

#endif // DISPLAY_H
