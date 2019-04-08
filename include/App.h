#ifndef APP_CORE_H
#define APP_CORE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "GLSLProgram.h"

#include "Cube.h"
#include "SpotLight.h"
#include "Camera.h"

class App
{
	GLFWwindow *window;
	GLuint vao, vbo, ibo;
	GLSLProgram *shader;

	Camera camera;

	SpotLight *light;

	std::vector<Cube*> cubes;

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
