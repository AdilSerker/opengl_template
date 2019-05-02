#include "PointLight.h"

PointLight::PointLight() :
	position(glm::vec3(0.0, 0.0, 0.0)),
	rotationAxis(glm::vec3(1.0, 1.0, 1.0)),
	rotationAngle(0.0f),
	scale(glm::vec3(1.0f)),
	color(glm::vec3(1.0f)),
	ambient(glm::vec3(0.1f, 0.1f, 0.1f)),
	diffuse(glm::vec3(0.5f, 0.5f, 0.5f)),
	specular(glm::vec3(1.0f, 1.0f, 1.0f))
{

	this->shader = new GLSLProgram();

	shader->compileShader("./shaders/light.vs", GLSLShader::VERTEX);
	shader->compileShader("./shaders/light.fs", GLSLShader::FRAGMENT);

	shader->link();
	shader->use();
	
	setUniforms(this->shader);

	initBuffers();
}

void PointLight::setUniforms(GLSLProgram *shader)
{
	shader->setUniform("pointLight.position", position);
	shader->setUniform("pointLight.ambient", ambient);
	shader->setUniform("pointLight.diffuse", diffuse);
	shader->setUniform("pointLight.specular", specular);
}

void PointLight::setUniforms(GLSLProgram *shader, glm::vec3 color)
{
	shader->setUniform("pointLight.position", position);
	shader->setUniform("pointLight.ambient", color);
	shader->setUniform("pointLight.diffuse", color);
	shader->setUniform("pointLight.specular", color);
}

PointLight::~PointLight() {}

void PointLight::initBuffers()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
}

void PointLight::draw(glm::mat4 view, glm::mat4 proj)
{
	shader->use();

	glBindVertexArray(vao);

	this->setUniforms(shader, color);

	shader->setUniform("ViewMatrix", view);
	shader->setUniform("ProjMatrix", proj);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotationAngle, rotationAxis);
	model = glm::scale(model, scale);
	shader->setUniform("ModelMatrix", model);

	glm::mat4 modelView = view * model;
	shader->setUniform("NormalMatrix", glm::mat3(glm::vec3(modelView[0]), glm::vec3(modelView[1]), glm::vec3(modelView[2])));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
