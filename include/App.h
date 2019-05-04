#ifndef APP_CORE_H
#define APP_CORE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "GLSLProgram.h"

#include "Cube.h"
#include "Camera.h"
#include "Model.h"

#include "PointLight.h"
#include "DirectionLight.h"

class App
{
	GLFWwindow *window;
	GLuint vao, vbo, ibo;
	GLSLProgram *shader;

	Camera *camera;

	PointLight *light;
	DirectionLight *dirLight;

	// std::vector<Cube*> cubes;
	std::vector<Model*> models;

	void initWindow();
	void update();
	void render();

  public:
	App();
	~App();
	void init();
	void run();
};

#endif //APP_CORE_H
