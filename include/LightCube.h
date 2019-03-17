#ifndef LIGHT_CUBE
#define LIGHT_CUBE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL/SOIL.h>

#include "GLSLProgram.h"

class LightCube
{
  private:
    GLuint vao, vbo;
    GLSLProgram shader;
    
    void initBuffers();

  public:
    LightCube();
    ~LightCube();

    glm::vec3 position;
    void draw(glm::mat4 view, glm::mat4 proj);
};


#endif