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

    this->camera = new Camera();
    shapes.push_back(new Plane(5000.0f, 5000.0f, 1, 1));

    float shiftX = 8.0f;
    float shiftY = 9.0f;

    for (int i = 1; i < 10; ++i) {
        glm::vec3 pos = glm::vec3(i*shiftX, 0.0f, i*shiftY);
            
        shapes.push_back(new Teapot(55, glm::mat4(1.0f), pos));
    }

    shader.setUniform("Fog.maxDist", 70.0f );
    shader.setUniform("Fog.minDist", 1.0f );
    shader.setUniform("Fog.color", vec3(0.5f,0.5f,0.5f) );

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

    shader.setUniform("Light.position", view * glm::vec4(0.0f, 1.0f, 1.0f, 0.0f) );
    shader.setUniform("Light.intensity", vec3(0.8f,0.8f,0.8f) );

    for (std::vector<TriangleMesh *>::iterator it = shapes.begin(); it != shapes.end(); ++it)
    {
        (*it)->render(&shader, view, projection);
    }
}
