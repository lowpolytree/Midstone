#pragma once
#include "Scene.h"
#include "glew.h"
#include "glm//matrix.hpp"
#include <memory>

class Camera;

class Scene4 : public Scene
{
public:
	Scene4();
	~Scene4();

	bool Create();
	void HandleEvents(const SDL_Event& ev);
	void Update(float deltatime);
	void Render();

	void RenderPassOne();
	void RenderPassTwo();

private:
	std::unique_ptr<class DemoObject> monkey;
	std::shared_ptr<class Mesh>       monkeyMesh;
	std::shared_ptr<class Texture>    monkeyTex;

	std::unique_ptr<class DemoObject> plane;
	std::shared_ptr<class Mesh>       planeMesh;
	std::shared_ptr<class Texture>    planeTex;

	std::shared_ptr<class Shader> shader;
	std::shared_ptr<class Shader> shadowPass1Shader;
	std::shared_ptr<class Shader> shadowPass2Shader;

	std::unique_ptr<class Camera> camera;

	float tempdeltatime;

	GLuint shadowBuffer;
	GLuint shadowTex;
	glm::mat4 lightViewM;
	glm::mat4 lightProjM;
	glm::mat4 shadowMVP1;
	glm::mat4 shadowMVP2;
	glm::mat4 biasMatrix;
};
