#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::mat4;
using glm::vec3;

#include <iostream>

#include "Plane.h"
#include "Torus.h"
#include "Teapot.h"

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

    shapes.push_back(new Teapot(13, glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.25f))));

    this->camera = new Camera();

    glm::vec4 worldLight = glm::vec4(50.0f, 50.0f, 2.0f, 1.0f);

    shader.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
    shader.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    shader.setUniform("Light.Position", worldLight);
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

    mat4 model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(-45.0f), vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(-45.0f), vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(-45.0f), vec3(0.0, 1.0, 1.0));

    mat4 mv = view * model;
    shader.setUniform("ModelViewMatrix", mv);
    shader.setUniform("MVP", projection * mv);
}

void Scene::render()
{

    setMatrices();

    for (std::vector<TriangleMesh *>::iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        (*it)->render();
    }
}
