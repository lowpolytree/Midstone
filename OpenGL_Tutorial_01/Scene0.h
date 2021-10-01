#ifndef SCENE0_H
#define SCENE0_H
#include "Scene.h"
#include "glm//matrix.hpp"

class Scene0 : public Scene
{
public:
	Scene0();
	~Scene0();

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

	glm::mat4 modelM{ 1.0f };
	glm::mat4 viewM{ 1.0f };
};

#endif