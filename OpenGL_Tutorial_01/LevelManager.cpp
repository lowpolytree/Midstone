#include "LevelManager.h"
#include "Game.h"
#include "GameOver.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"

int LevelManager::levelCounter = 1;

void LevelManager::LoadLevel(const Scene type)
{
	if (type == Scene::GAME_OVER) {
		Game::gameStateMachine->ChangeLevel(new GameOver());
	}

	if (type == Scene::LEVEL)
	{
		Game::gameStateMachine->ChangeLevel(new Level5());
	}

	/*if (type == Scene::LEVEL) {
		switch (levelCounter) 
		{
			case 1:
				Game::gameStateMachine->ChangeLevel(new Level1());
			break;
			case 2:
				Game::gameStateMachine->ChangeLevel(new Level2());
			break;
			case 3: 
				Game::gameStateMachine->ChangeLevel(new Level3());
			break;
			case 4:
				Game::gameStateMachine->ChangeLevel(new Level4());
			break;
		}
	}*/
}