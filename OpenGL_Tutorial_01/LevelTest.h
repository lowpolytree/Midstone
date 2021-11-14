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

	bool OnEnter() override;
	bool OnExit() override;

	void HandleEvents(const SDL_Event& ev) override;
	void Update(float deltatime) override;
	void Render() override;

	virtual std::string getStateID() const override { return ""; }

private:
	std::unique_ptr<class Camera> camera;
	std::unique_ptr<class Fire> fire;

	float tempdeltatime;
};
