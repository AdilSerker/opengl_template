#ifndef APP_CORE_H
#define APP_CORE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "Camera.h"
#include "Terrain.h"

#include "TriangleMesh.h"

class App
{
	GLFWwindow *window;

	Camera *camera;

	Scene *scene;
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
