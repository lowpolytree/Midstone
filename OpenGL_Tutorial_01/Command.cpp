#include "Command.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

void QuitCommand::Execute()
{
	Game::s_isRunning = false;
}

void PlayCommand::Execute()
{
	Game::gameStateMachine->ChangeLevel(new Level2());
}
