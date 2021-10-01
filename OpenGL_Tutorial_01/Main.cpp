#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {

	Game *game = new Game();
	Game::s_isRunning = game->Init();
	game->Create();
	while (Game::s_isRunning) {
		game->Run();
	}

	return 0;
}