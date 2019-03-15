#ifndef POLY_H
#define POLY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL.h>

#include "GLSLProgram.h"

class Poly
{
  private:
    GLuint vao, vbo, ibo;
    GLuint tex1, tex2;
    GLSLProgram shader;

    void initBuffers();
    void initTexture();

  public:
    Poly();
    ~Poly();

    void draw(glm::mat4 view, glm::mat4 proj);
};

#endif
