#pragma once
#include "Level.h"
#include "glew.h"
#include "glm//matrix.hpp"
#include <memory>

class Camera;

class Level1 : public Level
{
public:
	Level1();

	bool OnEnter() override;
	bool OnExit() override;

	void HandleEvents(const SDL_Event& ev) override;
	void Update(float deltatime) override;
	void Render() override;

	virtual std::string getStateID() const override { return stateID; }

private:
	std::unique_ptr<class Camera> camera;
	std::unique_ptr<class Map> map;
	std::unique_ptr<class DemoObject> ground;
	std::unique_ptr<class DemoObject> grass;
	std::unique_ptr<class Player> player;

	static const std::string stateID;
};
