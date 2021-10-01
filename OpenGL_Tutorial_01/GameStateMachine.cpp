#include "GameStateMachine.h"

void GameStateMachine::PushLevel(Level* level)
{
	levels.push_back(level);
	levels.back()->OnEnter();
}

void GameStateMachine::ChangeLevel(Level* level)
{
	if (!levels.empty()) {
		if (levels.back()->getStateID() == level->getStateID()) return;

		if (levels.back()->OnExit()) {
			delete levels.back();
			levels.pop_back();
		}
	}

	//Push back a new state.
	levels.push_back(level);
	levels.back()->OnEnter();
}

void GameStateMachine::PopLevel()
{
	if (levels.empty()) return;

	if (levels.back()->OnExit()) {
		delete levels.back();
		levels.pop_back();
	}
}

void GameStateMachine::HandleEvents(const SDL_Event& ev)
{
	if (levels.empty()) return;
	levels.back()->HandleEvents(ev);
}

void GameStateMachine::Update(float deltatime)
{
	if (levels.empty()) return;
	levels.back()->Update(deltatime);
}

void GameStateMachine::Render()
{
	if (levels.empty()) return;
	levels.back()->Render();
}
