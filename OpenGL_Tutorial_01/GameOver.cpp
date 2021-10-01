#include "GameOver.h"
#include "glew.h"
#include <iostream>

const std::string GameOver::stateID = "GAMEOVER";

bool GameOver::OnEnter()
{
	std::cout << "Entering GameOver!\n";
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 500 }, Size{ 256.0f, 68.0f }, "REPLAY", std::make_unique<PlayCommand>()));
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 400 }, Size{ 256.0f, 68.0f }, "QUIT", std::make_unique<QuitCommand>()));

	return true;
}

bool GameOver::OnExit()
{
	std::cout << "Exiting GameOver!\n";
	return true;
}

void GameOver::HandleEvents(const SDL_Event& ev) {
	for (const auto& button : buttons) {
		if (!button->getIsActive()) break;
		button->HandleEvents(ev);
	}
}

void GameOver::Update(float deltatime) {}

void GameOver::Render() {

	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto& button : buttons) {
		button->Render();
	}
}
