#include "LightCube.h"

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

LightCube::LightCube()
{

	shader.compileShader("./shaders/light.vs", GLSLShader::VERTEX);
	shader.compileShader("./shaders/light.fs", GLSLShader::FRAGMENT);

	shader.link();
	shader.use();

	position = glm::vec3(0.2f, 2.8f, -3.25f);

	initBuffers();
}

LightCube::~LightCube() {}

void LightCube::initBuffers()
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, 0.5f, -0.5f, 
		0.5f, 0.5f, -0.5f, 
		-0.5f, 0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f, 
		0.5f, 0.5f, 0.5f, 
		0.5f, 0.5f, 0.5f, 
		-0.5f, 0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f, 
		-0.5f, 0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f, 

		0.5f, 0.5f, 0.5f, 
		0.5f, 0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f, 

		-0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f, 

		-0.5f, 0.5f, -0.5f, 
		0.5f, 0.5f, -0.5f, 
		0.5f, 0.5f, 0.5f, 
		0.5f, 0.5f, 0.5f, 
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	glBindVertexArray(0);
}

void LightCube::draw(glm::mat4 view, glm::mat4 proj)
{
	shader.use();

	glBindVertexArray(vao);

	shader.setUniform("objColor", glm::vec3(1.0f, 1.0f, 1.0f));

	shader.setUniform("V", view);
	shader.setUniform("P", proj);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 1.0f, -1.0f));
	model = glm::scale(model, glm::vec3(0.1f));
	shader.setUniform("M", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	
}

