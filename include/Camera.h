#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLSLProgram.h"

class Camera
{
  public:
	Camera();
	void update(GLFWwindow *window);
	glm::mat4 getViewMatrix() const { return ViewMatrix; }
	glm::mat4 getProjectionMatrix() const { return ProjectionMatrix; }
	glm::vec3 getPosition() const { return pos; }
	void setUniforms(GLSLProgram *shader);

  private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	float horizontalAngle;
	float verticalAngle;

	glm::vec3 pos;
};

#endif //CAMERA_H
