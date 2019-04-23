#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL.h>

#include "GLSLProgram.h"

class SpotLight
{
  private:
    GLuint vao, vbo, ibo;
    GLuint tex1, tex2;

    void initBuffers();
    void initTexture();

    GLSLProgram *shader;

  public:
    SpotLight();
    ~SpotLight();

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;

    glm::vec3 color;

    glm::vec3 ambient;
    glm::vec3 specular;
    glm::vec3 diffuse;

    void draw(glm::mat4 view, glm::mat4 proj);
    void setUniforms(GLSLProgram *shader);
};

#endif
