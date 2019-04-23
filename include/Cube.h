#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL.h>

#include "GLSLProgram.h"

class Cube
{
  private:
    GLuint vao, vbo, ibo;
    GLuint diffuseMap, specularMap;

    void initBuffers();
    void initTexture();

  public:
    Cube();
    ~Cube();

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;

    float specular;
    float shininess;

    void draw(GLSLProgram *shader, glm::mat4 view, glm::mat4 proj);
};

#endif
