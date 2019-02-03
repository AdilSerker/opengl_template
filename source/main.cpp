#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow *window = nullptr;

#include <glm/glm.hpp>
using namespace glm;
using namespace std;

#include "Scene.h"

Scene *scene = nullptr;

enum
{
    WINDOW_WIDTH = 1600,
    WINDOW_HEIGHT = 900
};

void initWindow()
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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL template", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Window initialization error\n");
        glfwTerminate();
        exit(-1);
    }
    glfwSetWindowPos(window, mode->width / 2 - WINDOW_WIDTH / 2, mode->height / 2 - WINDOW_HEIGHT / 2);
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "GLEW Initialization error\n");
        exit(-1);
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
}

void mainLoop()
{
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete scene;
    glfwTerminate();
}

int main()
{
    initWindow();

    scene = new Scene();
    scene->initScene();

    mainLoop();

    return 0;
}
