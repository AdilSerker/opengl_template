#include "Camera.h"
#include "text2D.hpp"

Camera::Camera()
{
    pos   = glm::vec3(0.0f, 15.0f, 15.0f);

    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
}

void Camera::update(GLFWwindow *window)
{
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int WINDOW_WIDTH = mode->width;
    int WINDOW_HEIGHT = mode->height;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    GLfloat cameraSpeed = 0.1f;
    GLfloat mouseSpeed = 0.005f;

    horizontalAngle += mouseSpeed * float(WINDOW_WIDTH/2 - xpos );
	verticalAngle   += mouseSpeed * float(WINDOW_HEIGHT/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        pos += cameraSpeed * direction;
    }
    
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        pos -= cameraSpeed * direction;
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        pos += right * cameraSpeed;
    }
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        pos -= right * cameraSpeed;
    }
    
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        pos += up * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        pos -= up * cameraSpeed;
    }
    ProjectionMatrix = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.0f);

    ViewMatrix = glm::lookAt(
        pos,
        pos + direction,
        up
    );

    // lastTime = currentTime;
}

void Camera::setUniforms(GLSLProgram *shader)
{
	shader->setUniform("viewPos", pos);
}