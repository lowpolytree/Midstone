#pragma once

union SDL_Event;

class GameObject {

public:
	virtual bool Create() = 0;
	virtual void HandleEvents(const SDL_Event &ev) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
};
