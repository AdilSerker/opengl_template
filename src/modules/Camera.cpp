#include "Camera.h"
#include <iostream>

Camera::Camera()
{
    pos   = glm::vec3(0.0f, 0.0f,  3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up    = glm::vec3(0.0f, 1.0f,  0.0f);
}

void Camera::computeMatricesFromInputs(GLFWwindow *window)
{
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int WINDOW_WIDTH = mode->width;
    int WINDOW_HEIGHT = mode->height;
    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    GLfloat cameraSpeed = 0.01f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        pos += cameraSpeed * front;
    }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        pos -= cameraSpeed * front;
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;
    }
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    }
    
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        pos += up * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        pos -= up * cameraSpeed;
    }
    ProjectionMatrix = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.0f);

    ViewMatrix = glm::lookAt(
        pos,
        pos + front,
        up
    );

    lastTime = currentTime;
}