#include "Poly.h"

Poly::Poly()
{
	init();
}

Poly::~Poly() {}

void Poly::init()
{
	shader.compileShader("./shaders/triangle.vs", GLSLShader::VERTEX);
	shader.compileShader("./shaders/triangle.fs", GLSLShader::FRAGMENT);

	shader.link();
	shader.use();

	GLfloat vertices[] = {
		0.0f, 0.8f, 0.0f, 0.3f, 0.7f, 0.7f, 0.5f, 1.3f,
		0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.2f, 0.2f,		// Top Right
		0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.2f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom Left
		-0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, 0.2f,   // Top Left
	};
	GLuint indices[] = {
		// Note that we start from 0!
		0, 1, 4, // First Triangle
		1, 2, 4,
		2, 3, 4 // Second Triangle
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));

	glBindVertexArray(0);

	int width, height;

	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char *image = SOIL_load_image("./texture/frac.png", &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	image = SOIL_load_image("./texture/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Poly::draw()
{
	shader.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1);
	shader.setUniform("ourTexture1", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	shader.setUniform("ourTexture2", 1);

	glBindVertexArray(vao);

	glm::mat4 model = glm::mat4(1.0f);

	GLfloat timeValue = glfwGetTime();
	GLfloat greenValue = (sin(timeValue) / 2) + 0.5;

	glm::mat4 translate = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotate = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scale = glm::scale(model, glm::vec3(2.0f));

	shader.setUniform("transform", translate * rotate * scale);
	shader.setUniform("mixf", greenValue);

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}