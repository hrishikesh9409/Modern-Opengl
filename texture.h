#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream>

class texture
{
    public:
        texture(const std::string& fileName);

        void bindTexture(unsigned int unit);

        virtual ~texture();
    private:
        GLuint tex;
};

#endif // TEXTURE_H
