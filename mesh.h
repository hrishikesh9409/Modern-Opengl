#ifndef MESH_H
#define MESH_H

#include "obj_loader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class vertex{
    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
        glm::vec3 normal;
    public:

        inline glm::vec3* GetPos()  { return &pos; }
        inline glm::vec2* GetTexCoord() {   return &texCoord;   }
        inline glm::vec3* GetNormal()   {   return &normal; }

        vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0)){
            this->pos = pos;
            this->texCoord = texCoord;
            this->normal = normal;
        }
};

class mesh
{
    public:

        mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
        mesh(const std::string& fileName);

        void Draw();

        virtual ~mesh();

    private:

        void initMesh(const IndexedModel& model);

        enum{
            POSITION_VB,
            TEXCOORD_VB,
            NORMAL_VB,

            INDEX_VB,

            NUM_BUFFERS
        };

        GLuint vertexArrayObject;
        GLuint vertexArrayBuffers[NUM_BUFFERS];
        unsigned int drawCount;
};

#endif // MESH_H
