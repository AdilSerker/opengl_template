#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "GLSLProgram.h"

#include <SOIL/SOIL.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int textureFromFile(const char *path, const string &directory, bool gamma = false);

class Model 
{
public:
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;

    Model(string const &path, bool gamma = false) :
            gammaCorrection(gamma),
            position(glm::vec3(0.0, 0.0, 0.0)),
            rotationAxis(glm::vec3(1.0, 1.0, 1.0)),
            rotationAngle(0.0f),
            scale(glm::vec3(1.0f))
    {
        loadModel(path);
    }

    void draw(GLSLProgram *shader, glm::mat4 view, glm::mat4 proj);
    
private:
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif
