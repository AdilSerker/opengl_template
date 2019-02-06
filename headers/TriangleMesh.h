#ifndef TRIANGLE_MESH
#define TRIANGLE_MESH

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "GLSLProgram.h"

class TriangleMesh
{
  protected:
    GLuint nVerts;
    GLuint vao;

    std::vector<GLuint> buffers;

    virtual void initBuffers(
        std::vector<GLuint> *indices,
        std::vector<GLfloat> *points,
        std::vector<GLfloat> *normals,
        std::vector<GLfloat> *texCoords = nullptr,
        std::vector<GLfloat> *tangents = nullptr);

    virtual void deleteBuffers();

  public:
    virtual ~TriangleMesh();
    virtual void render(GLSLProgram *shader, glm::mat4 view, glm::mat4 proj);
    GLuint getVao() const { return vao; }
};

#endif //TRIANGLE_MESH
