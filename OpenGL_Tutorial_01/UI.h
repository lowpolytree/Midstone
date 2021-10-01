#pragma once

union SDL_Event;

struct Size {
	float width;
	float height;
};

struct Position {
	float x;
	float y;
};

class UI
{
public:
	virtual void OnCreate() = 0;
	virtual void HandleEvents(const SDL_Event& ev) = 0;
	virtual void Render() = 0;
};

