#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
  public:
	Camera();
	void computeMatricesFromInputs(GLFWwindow *window);
	glm::mat4 getViewMatrix() const { return ViewMatrix; }
	glm::mat4 getProjectionMatrix() const { return ProjectionMatrix; }

  private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
};

#endif //CAMERA_H