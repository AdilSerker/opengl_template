#ifndef APP_CORE_H
#define APP_CORE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLSLProgram.h"

#include "Poly.h"
#include "LightCube.h"
#include "Camera.h"

class App
{
	GLFWwindow *window;
	GLuint vao, vbo, ibo;
	GLSLProgram *shader;

	Camera camera;

	Poly *one;
	LightCube *two;

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
