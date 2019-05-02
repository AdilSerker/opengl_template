#ifndef DIRECTION_LIGHT_H
#define DIRECTION_LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLSLProgram.h"

class DirectionLight
{
private:
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

public:
    DirectionLight();
    ~DirectionLight();

    void setUniforms(GLSLProgram *shader);
};

#endif
