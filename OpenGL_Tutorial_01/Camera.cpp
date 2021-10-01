#include "Camera.h"
#include "glew.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(){}
Camera::~Camera(){}

void Camera::sendProjToShader(const std::shared_ptr<Shader>& shader, const std::string& name) const
{
	shader->useProgram();
	auto loc = glGetUniformLocation(shader->getShaderID(), name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projM));
}
