#pragma once
#include "Level.h"
#include <vector>

class GameStateMachine
{
public:
	void PushLevel(Level* level);
	void ChangeLevel(Level* level);
	void PopLevel();

	void HandleEvents(const SDL_Event& ev);
	void Update(float deltatime);
	void Render();

private:
	std::vector<Level*> levels;
};

