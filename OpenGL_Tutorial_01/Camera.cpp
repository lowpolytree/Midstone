#include "Camera.h"
#include "glew.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

const auto UP_VECTOR = glm::vec3{ 0.0f, 1.0f, 0.0f };

Camera::Camera(){}
Camera::~Camera(){}

void Camera::sendProjToShader(const std::shared_ptr<Shader>& shader, const std::string& name) const
{
	shader->useProgram();
	auto loc = glGetUniformLocation(shader->getShaderID(), name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projM));
}

void Camera::SetUpCamera(const float mapMidpoint, const float height, const float offset)
{
	projM = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	auto position = glm::vec3{ mapMidpoint, height, mapMidpoint + offset };
	auto target = glm::vec3{ mapMidpoint, 0.0f, -mapMidpoint };

	viewM = glm::lookAt(position, target, UP_VECTOR);
}
