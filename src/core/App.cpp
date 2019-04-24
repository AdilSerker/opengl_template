#include "App.h"

#include <iostream>
using namespace std;

#include "text2D.hpp"

#include "Cube.h"

void App::update()
{
	camera.update(window);

	light->position.x = 3 * sin(glfwGetTime());
	light->position.z = 3 * cos(glfwGetTime());

	Cube *one = cubes[0];
	one->rotationAngle = (GLfloat)glfwGetTime() * 0.4f;
}

void App::render()
{
	light->draw(camera.getViewMatrix(), camera.getProjectionMatrix());

	shader->use();
	light->setUniforms(this->shader);

	auto it = cubes.begin();
	for (auto stop = cubes.end(); it != stop; ++it)
	{
		(*it)->draw(shader, camera.getViewMatrix(), camera.getProjectionMatrix());
	}
}

App::App()
{
}

App::~App() {}

void App::init()
{
	initWindow();
	initText2D("./fonts/Holstein.DDS");

	this->shader = new GLSLProgram();

	shader->compileShader("./shaders/general.vs", GLSLShader::VERTEX);
	shader->compileShader("./shaders/general.fs", GLSLShader::FRAGMENT);

	shader->link();
	shader->use();

	this->light = new SpotLight();
	this->light->scale = glm::vec3(0.05f);
	this->light->position = glm::vec3(10.0f, 0.0f, 10.0f);

	Cube *one = new Cube();
	Cube *two = new Cube();

	one->scale = glm::vec3(0.8f);

	two->position = glm::vec3(0.0f, -2.8f, 0.0f);
	two->scale = glm::vec4(4.0f);

	cubes.push_back(one);
	cubes.push_back(two);
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

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

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
		char fps[256];

		if (currentTime - lastTime >= 1.0)
		{
			sprintf(fps, "%i fps", nbFrames);
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

		printText2D(fps, 10, 10, 20);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	cleanupText2D();
	glfwTerminate();
}
