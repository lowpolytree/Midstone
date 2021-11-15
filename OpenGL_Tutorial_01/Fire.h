#pragma once
#include <memory>
#include "glm/vec3.hpp"

class Fire
{
public:
	Fire();

	bool Load(const std::shared_ptr<class Mesh>& mesh, const std::shared_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& tex);
	void Update(float deltatime);
	void Render();

	void SetPosition(const glm::vec3& position);

private:
	std::unique_ptr<class DemoObject> flame1;
	glm::vec3 position1;
	float time1;

	std::unique_ptr<class DemoObject> flame2;
	glm::vec3 position2;
	float time2;

	std::unique_ptr<class DemoObject> flame3;
	glm::vec3 position3;
	float time3;
};

