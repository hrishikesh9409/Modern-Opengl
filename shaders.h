#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <fstream>
#include "transform.h"
#include "camera.h"

class shaders
{
    public:

        shaders(const std::string& fileName);

        void Bind();
        void UpdateTransformations(const Transform& trans, const camera& cam);

        GLuint createShader(const std::string& text, GLenum ShaderType);

        virtual ~shaders();

    private:

        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;

        enum{
            TRANSFORM_U,

            NUM_UNIFORMS
        };

        GLuint uniforms[NUM_UNIFORMS];

        void linkProgram(GLuint program, GLuint ShaderType);
};

#endif // SHADERS_H
