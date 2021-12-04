#include "Command.h"
#include "LevelManager.h"

void QuitCommand::Execute()
{
	Game::s_isRunning = false;
}

void PlayCommand::Execute()
{
	LevelManager::LoadLevel(Scene::LEVEL);
}

void ReplayCommand::Execute()
{
	LevelManager::LoadLevel(Scene::LEVEL);
}

void ToMenuCommand::Execute()
{
	LevelManager::levelCounter = 1;
	LevelManager::LoadLevel(Scene::MENU);
}
