#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;
using glm::vec3;

#include <iostream>

Scene::~Scene()
{
    for (std::vector<TriangleMesh *>::iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        delete (*it);
    }

    shapes.clear();
    delete camera;
}

void Scene::initScene()
{
    compileAndLinkShader();

    shapes.push_back(new Plane(10, 10, 100, 100));
    shapes.push_back(new Torus(4, 2, 50, 50));

    this->camera = new Camera();

    glm::vec4 worldLight = glm::vec4(5.0f, 5.0f, 2.0f, 1.0f);

    shader.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
    shader.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    shader.setUniform("Light.Position", view * worldLight);
    shader.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
    shader.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
    shader.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    shader.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
    shader.setUniform("Material.Shininess", 100.0f);
}

void Scene::compileAndLinkShader()
{
    shader.load("./shaders/phong.vert", "./shaders/phong.frag");

    shader.use();
}

void Scene::setMatrices()
{
    camera->computeMatricesFromInputs();
    view = camera->getViewMatrix();
    projection = camera->getProjectionMatrix();

    mat4 mv = view * model;
    shader.setUniform("ModelViewMatrix", mv);
    shader.setUniform("NormalMatrix",
                      glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    shader.setUniform("MVP", projection * mv);
}

void Scene::render()
{

    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(35.0f), vec3(0.0f, 1.0f, 0.0f));
    setMatrices();

    for (std::vector<TriangleMesh *>::iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        (*it)->render();
    }
}
