#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "glm//matrix.hpp"
#include <stack>

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	void Create();
	void HandleEvents(const SDL_Event& ev);
	void Update(float deltatime);
	void Render();

private:
	class DemoObject* monkey;
	class DemoObject* monkey1;
	class DemoObject* monkey2;
	class Mesh* mesh;
	class Texture* tex;
	class Shader* shader;

	std::stack<glm::mat4> mvStack;

	glm::mat4 modelM1 { 1.0f };
	glm::mat4 modelM2{ 1.0f };
	glm::mat4 viewM  { 1.0f };
	glm::mat4 projM{ 1.0f };

	float tempdeltatime;
};

#endif