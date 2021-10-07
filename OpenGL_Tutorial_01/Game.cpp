#include <iostream>
#include "Game.h"
#include "SDL_ttf.h"
#include "glew.h"
#include "Timer.h"
#include "Level1.h"
#include "ResourceLoader.h"
#include "Menu.h"
#include "GameOver.h"

bool Game::s_isRunning = false;
SDL_Window* Game::win = nullptr;
GameStateMachine* Game::gameStateMachine = nullptr;

Game::Game(): glContext(nullptr), currentLevel(nullptr), timer(nullptr){}

Game::~Game(){
	if (gameStateMachine) delete gameStateMachine, gameStateMachine = nullptr;
	if (timer) delete timer, timer = nullptr;
	if (glContext) SDL_GL_DeleteContext(glContext);
	if (win) SDL_DestroyWindow(win);
	SDL_Quit();
}

bool Game::Init(){
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Error: Unable to initialize SDL!\n";
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "Error: Unable to initialize SDL_TFF!\n";
	}

	win = SDL_CreateWindow("Welcome To OpenGL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280, 720, SDL_WINDOW_OPENGL);
	if (!win) {
		std::cout << "Error: Couldn't create a window!\n";
		SDL_Quit();
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glContext = SDL_GL_CreateContext(win);

	//Initialize Glew to call opengl functions.
	GLenum status = glewInit();
	if (GLEW_OK != status)
	{
		std::cout << "Error: Unable to initialize GLEW!\n";
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return false;
	}
	else
		std::cout << "Glew is OK!\n";

	return true;
}

void Game::Create(){
	//BUILD A NEW SCENE/////////////////////////////////////////

	timer = new Timer();
	if (timer == nullptr) {
		std::cout << "The Timer failed to build!\n";
	}

	//LOADING RESOURCES
	if (!ResourceLoader::LoadResources()) {
		std::cout << "ERROR: Resources failed to load!\n";
		false;
	}

	gameStateMachine = new GameStateMachine();
	if (gameStateMachine == nullptr) {
		std::cout << "The Game State Machine failed to build!\n";
	}
	//gameStateMachine->ChangeLevel(new Level0());
	gameStateMachine->PushLevel(new Menu());
}

void Game::Run(){
	timer->Start();
	SDL_Event ev;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	while(s_isRunning) {
		timer->UpdateFrameTicks();

		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				s_isRunning = false;
			gameStateMachine->HandleEvents(ev);
		}
		gameStateMachine->Update(timer->GetDeltaTime());

		gameStateMachine->Render();

		SDL_GL_SwapWindow(win);
	}
}