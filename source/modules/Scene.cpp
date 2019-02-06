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
    this->camera = new Camera();
    shapes.push_back(new Plane(100.0f, 100.0f, 1, 1));
    shapes.push_back(new Teapot(13, glm::mat4(1.0f)));

    compileAndLinkShader();
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
}

void Scene::render()
{
    setMatrices();

    shader.setUniform("LightPosition", view * glm::vec4(0.0f, 100.0f, 100.0f, 0.0f) );
    shader.setUniform("LightIntensity", vec3(0.8f,0.8f,0.8f) );

    for (std::vector<TriangleMesh *>::iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        (*it)->render(&shader, view, projection);
    }
}
