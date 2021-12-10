#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "GameStateMachine.h"

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Create();
	void Run();

	static bool s_isRunning;
	static SDL_Window* win;
	static GameStateMachine* gameStateMachine;

private:
	SDL_GLContext glContext;
	class Level *currentLevel;
	class Timer* timer;
	//class Mix_Music* music;
};
