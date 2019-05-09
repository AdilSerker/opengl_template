#include "App.h"

#include <string>
#include <iostream>
using namespace std;

#include "text2D.hpp"

#include "Cube.h"

void printg(string info, int value, int y);

void App::update()
{
	camera->update(window);

	light->position.x = -5 * sin(glfwGetTime());
	light->position.z = 5 * cos(glfwGetTime());

	// light->position = camera->getPosition();

	models[0]->rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	models[0]->rotationAngle = (GLfloat)glfwGetTime() * 0.4f;

	this->cubemap->position = camera->getPosition(); 

}

void App::render()
{
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 proj = camera->getProjectionMatrix();
	light->draw(view, proj);

	shader->use();
	camera->setUniforms(this->shader);

	light->setUniforms(this->shader);
	dirLight->setUniforms(this->shader);

	auto it = models.begin();
	for (auto stop = models.end(); it != stop; ++it)
	{
		(*it)->draw(this->shader, view, proj);
	}
	cubemap->draw(view, proj);
	printg("cam_pos.x", (int)camera->getPosition().x, 40);
	printg("cam_pos.y", (int)camera->getPosition().y, 60);
	printg("cam_pos.z", (int)camera->getPosition().z, 80);
}

App::App()
{
}

App::~App() {}

void App::init()
{
	initWindow();
	initText2D("./fonts/Holstein.DDS");

	this->camera = new Camera();

	this->shader = new GLSLProgram();

	shader->compileShader("./shaders/ml.vs", GLSLShader::VERTEX);
	shader->compileShader("./shaders/ml.fs", GLSLShader::FRAGMENT);

	shader->link();
	shader->use();

	this->light = new PointLight();
	this->light->scale = glm::vec3(0.05f);
	this->light->position = glm::vec3(10.0f, 10.0f, 10.0f);

	this->cubemap = new CubeMap();
	this->cubemap->scale = glm::vec3(499.0f);

	this->dirLight = new DirectionLight();

	Model *nanosuit = new Model("./models/nanosuit/nanosuit.obj");
	// nanosuit->scale = glm::vec3(0.006f);

	models.push_back(nanosuit);
}

void App::initWindow()
{
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW Initialization error\n");
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int WINDOW_WIDTH = mode->width;
	int WINDOW_HEIGHT = mode->height;

	window = glfwCreateWindow(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		"OpenGL template",
		// NULL,
		glfwGetPrimaryMonitor(),
		NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Window initialization error\n");
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "GLEW Initialization error\n");
		exit(-1);
	}

	glViewport(0, 0, WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	// glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
}

double currentTimeInMs()
{
	return glfwGetTime() * 1000;
}

void App::run()
{

	double MS_PER_TICK = 1000 / 60;
	double PROCESSED_TIME = currentTimeInMs();
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		static int fps = 0;

		if (currentTime - lastTime >= 1.0)
		{
			fps = nbFrames;
			nbFrames = 0;
			lastTime += 1.0;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		while ((PROCESSED_TIME + MS_PER_TICK) < currentTimeInMs())
		{
			update();
			PROCESSED_TIME += MS_PER_TICK;
		}

		render();

		printg("fps", fps, 10);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	cleanupText2D();
	glfwTerminate();
}
