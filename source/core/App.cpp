#include "App.h"

#include <iostream>
using namespace std;

#include "text2D.hpp"

void App::update()
{
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int WINDOW_WIDTH = mode->width / 1.5;
	int WINDOW_HEIGHT = mode->height / 1.5;

	camera->computeMatricesFromInputs(window);
	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void App::render()
{
	scene->render(camera->getViewMatrix(), camera->getProjectionMatrix());
}

App::App()
{
	initWindow();

	scene = nullptr;

	camera = nullptr;
}

App::~App()
{
	delete scene;
	delete camera;
}

void App::init()
{
	this->scene = new Scene();
	scene->initScene();

	Terrain *ter = new Terrain(10000.0f, 512, 1800);
	scene->addShape(ter);
	this->camera = new Camera();

	initText2D("./fonts/Holstein.DDS");
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
	int WINDOW_WIDTH = mode->width / 1.5;
	int WINDOW_HEIGHT = mode->height / 1.5;

	window = glfwCreateWindow(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		"OpenGL template",
		NULL, 
		// glfwGetPrimaryMonitor(),
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

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0.71f, 0.95f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
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
		// char cameraPos[256];
		
		if (currentTime - lastTime >= 1.0)
		{
			sprintf(fps,"%i fps", nbFrames );
			// sprintf(cameraPos, "%f.2"); 


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
	
	cleanupText2D();
	glfwTerminate();
}
