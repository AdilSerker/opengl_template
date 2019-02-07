#ifndef TEAPOT_H
#define TEAPOT_H

#include "TriangleMesh.h"
#include <glm/glm.hpp>

class Teapot : public TriangleMesh
{
  private:
    //unsigned int faces;

    void generatePatches(std::vector<GLfloat> &p,
                         std::vector<GLfloat> &n,
                         std::vector<GLfloat> &tc,
                         std::vector<GLuint> &el, int grid);
    void buildPatchReflect(int patchNum,
                           std::vector<GLfloat> &B, std::vector<GLfloat> &dB,
                           std::vector<GLfloat> &v, std::vector<GLfloat> &n,
                           std::vector<GLfloat> &tc, std::vector<GLuint> &el,
                           int &index, int &elIndex, int &tcIndex, int grid,
                           bool reflectX, bool reflectY);
    void buildPatch(glm::vec3 patch[][4],
                    std::vector<GLfloat> &B, std::vector<GLfloat> &dB,
                    std::vector<GLfloat> &v, std::vector<GLfloat> &n,
                    std::vector<GLfloat> &tc, std::vector<GLuint> &el,
                    int &index, int &elIndex, int &tcIndex, int grid, glm::mat3 reflect,
                    bool invertNormal);
    void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);

    void computeBasisFunctions(std::vector<GLfloat> &B, std::vector<GLfloat> &dB, int grid);
    glm::vec3 evaluate(int gridU, int gridV, std::vector<GLfloat> &B, glm::vec3 patch[][4]);
    glm::vec3 evaluateNormal(int gridU, int gridV, std::vector<GLfloat> &B, std::vector<GLfloat> &dB, glm::vec3 patch[][4]);
    void moveLid(int grid, std::vector<GLfloat> &p, const glm::mat4 &lidTransform);

    glm::vec3 position;
  public:
    void setPosition(glm::vec3 pos);
    Teapot(int grid, const glm::mat4 &lidTransform, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));
    void render(GLSLProgram *shader, glm::mat4 view, glm::mat4 proj);

};

#endif //TEAPOT_H
