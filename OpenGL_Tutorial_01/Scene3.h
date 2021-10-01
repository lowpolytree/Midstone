#pragma once
#include "Scene.h"
#include "glm//matrix.hpp"
#include <memory>

class Camera;

class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();

	bool Create();
	void HandleEvents(const SDL_Event& ev);
	void Update(float deltatime);
	void Render();

private:
	std::unique_ptr<class DemoObject> monkey;
	std::shared_ptr<class Mesh>       monkeyMesh;
	std::shared_ptr<class Texture>    monkeyTex;

	std::unique_ptr<class DemoObject> plane;
	std::shared_ptr<class Mesh>       planeMesh;
	std::shared_ptr<class Texture>    planeTex;

	std::shared_ptr<class Shader> shader;

	std::unique_ptr<class Camera> camera;

	float tempdeltatime;
};
