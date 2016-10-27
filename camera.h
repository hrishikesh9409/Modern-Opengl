#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class camera
{
    public:
        camera(const glm::vec3& Campos, float fov, float aspect, float znear, float zfar){
            perspective = glm::perspective(fov, aspect, znear, zfar);
            position = Campos;
            Forward = glm::vec3(0,0,1);
            up = glm::vec3(0,1,0);
        }

        inline glm::mat4 GetViewProjection() const {
            return (perspective * glm::lookAt(position, position + Forward, up));
        }

    private:
        glm::mat4 perspective;
        glm::vec3 position;
        glm::vec3 Forward;
        glm::vec3 up;

};

#endif // CAMERA_H
