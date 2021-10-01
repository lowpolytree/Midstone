#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "glm//matrix.hpp"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	void Create();
	void HandleEvents(const SDL_Event &ev);
	void Update(float deltatime);
	void Render();

private:
	class SDL_Window* win;
	class DemoObject* monkey;
	class Mesh* mesh;
	class Texture* tex;
	class Shader* shader;

	glm::mat4* modelM;
	glm::mat4 viewM{ 1.0f };

	float tempdeltatime;
};

#endif