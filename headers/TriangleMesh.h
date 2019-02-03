#ifndef TRIANGLE_MESH
#define TRIANGLE_MESH

#include <vector>

#include <GL/glew.h>

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
    virtual void render() const;
    GLuint getVao() const { return vao; }
};

#endif //TRIANGLE_MESH
