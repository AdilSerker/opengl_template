#include "DirectionLight.h"

DirectionLight::DirectionLight() :
    direction(glm::vec3(0.0f, -1.0f, 0.0f)),
    ambient(glm::vec3(0.2f, 0.2f, 0.2f)),
	diffuse(glm::vec3(0.8f, 0.8f, 0.8f)),
	specular(glm::vec3(1.0f, 1.0f, 1.0f))
{}

void DirectionLight::setUniforms(GLSLProgram *shader)
{

	shader->setUniform("dirLight.direction", direction);
	shader->setUniform("dirLight.ambient", ambient);
	shader->setUniform("dirLight.diffuse", diffuse);
	shader->setUniform("dirLight.specular", specular);
}