#pragma once
#include "Level.h"
#include "glew.h"
#include "glm//matrix.hpp"
#include <memory>

class Camera;

class LevelTest : public Level
{
public:
	LevelTest();
	~LevelTest();

	bool Create();
	void HandleEvents(const SDL_Event& ev);
	void Update(float deltatime);
	void Render();

private:
	std::unique_ptr<class Camera> camera;
	std::unique_ptr<class Player> player;
	std::unique_ptr<class Player> player1;

	float tempdeltatime;
};
