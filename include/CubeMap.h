#ifndef CUBE_MAP_H
#define CUBE_MAP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL.h>

#include "GLSLProgram.h"

class CubeMap
{
  private:
    GLuint vao, vbo;
    GLuint cubeMapTex;

    GLSLProgram *shader;

    void initBuffers();
    void initTexture();

    void genTex(std::vector<std::string> faces);

  public:
    CubeMap();
    ~CubeMap();

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;

    void draw(glm::mat4 view, glm::mat4 proj);
};

#endif
