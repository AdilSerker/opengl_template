#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL.h>

#include "GLSLProgram.h"

class PointLight
{
  private:
    GLuint vao, vbo;

    void initBuffers();

    GLSLProgram *shader;

  public:
    PointLight();
    ~PointLight();

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;

    glm::vec3 color;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    void draw(glm::mat4 view, glm::mat4 proj);
    void setUniforms(GLSLProgram *shader);
    void setUniforms(GLSLProgram *shader, glm::vec3 color);
};

#endif
