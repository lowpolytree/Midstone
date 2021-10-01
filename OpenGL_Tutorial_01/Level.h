#pragma once
#include <string>

union SDL_Event;

class Level {
public:
	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;
	virtual void HandleEvents(const SDL_Event& ev) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
	virtual std::string getStateID() const = 0;
};