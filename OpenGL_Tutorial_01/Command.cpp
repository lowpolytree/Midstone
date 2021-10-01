#include "Command.h"
#include "Level0.h"

void QuitCommand::Execute()
{
	Game::s_isRunning = false;
}

void PlayCommand::Execute()
{
	Game::gameStateMachine->ChangeLevel(new Level0());
}
