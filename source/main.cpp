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
#include "Camera.h"

Scene *scene = nullptr;

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
    int WINDOW_WIDTH = mode->width;
    int WINDOW_HEIGHT = mode->height;

    window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "OpenGL template",
        glfwGetPrimaryMonitor(),
        NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Window initialization error\n");
        glfwTerminate();
        exit(-1);
    }

    std::cout << mode->width << "x" << mode->height << "\n";
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "GLEW Initialization error\n");
        exit(-1);
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    #ifndef __APPLE__
    glDebugMessageCallback(GLUtils::debugCallback, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, GL_DEBUG_SEVERITY_NOTIFICATION, -1 , "Start debugging");
    #endif
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
