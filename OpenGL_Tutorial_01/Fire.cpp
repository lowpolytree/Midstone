#include "Fire.h"
#include "DemoObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Fire::Fire(): position1(13.8f, 1.0f, -0.2f), time1(0.0f),
			  position2(14.0f, 1.0f, -0.4f), time2(-0.34f),
			  position3(14.2f, 1.0f,  0.0f), time3(-0.68f)
{}

bool Fire::Load(const std::shared_ptr<class Mesh>& mesh, const std::shared_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& tex)
{
	flame1 = std::make_unique<DemoObject>(mesh, shader, tex);
	flame2 = std::make_unique<DemoObject>(mesh, shader, tex);
	flame3 = std::make_unique<DemoObject>(mesh, shader, tex);
	
	if (!flame1 || !flame2 || !flame3) {
		std::cout << "ERROR: Flame failed to load!\n";
		return false;
	}

	return false;
}

void Fire::Update(float deltatime)
{
	if (time1 >= 1.0f)
		time1 = 0.0f;
	
	time1 += deltatime * 0.5f;

	if (time2 >= 1.0f)
		time2 = 0.0f;

	time2 += deltatime * 0.5f;

	if (time3 >= 1.0f)
		time3 = 0.0f;

	time3 += deltatime * 0.5f;
}

void Fire::Render()
{
	auto scale = glm::mix(0.5f, 0.2f, glm::clamp(time1, 0.0f, 1.0f));
	flame1->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, position1) * glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale }));
	flame1->sendFloatToShader("time", time1);
	flame1->Render();

	scale = glm::mix(0.5f, 0.2f, glm::clamp(time2, 0.0f, 1.0f));
	flame2->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, position2) * glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale }));
	flame2->sendFloatToShader("time", time2);
	if (time2 >= 0.0f)
		flame2->Render();

	scale = glm::mix(0.5f, 0.2f, glm::clamp(time3, 0.0f, 1.0f));
	flame3->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, position3) * glm::scale(glm::mat4{ 1.0f }, glm::vec3{ scale }));
	flame3->sendFloatToShader("time", time3);
	if (time3 >= 0.0f)
		flame3->Render();
}
