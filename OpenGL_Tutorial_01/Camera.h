#pragma once
#include "glm//matrix.hpp"
#include <string>
#include <memory>

class Shader;

class Camera
{
public:
	Camera();
	~Camera();

	auto& getViewMatrix() const { return viewM; }
	void setViewMatrix(const glm::mat4& vm) { viewM = vm; }

	auto& getProjMatrix() const { return projM; }
	void setProjMatrix(const glm::mat4& pm) { projM = pm; }

	void sendProjToShader(const std::shared_ptr<Shader>& shader, const std::string& name) const;

	void SetUpCamera(const float mapMidpoint, const float height, const float offset);

private:
	glm::mat4 viewM;
	glm::mat4 projM;
};

