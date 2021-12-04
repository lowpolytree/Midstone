#include "GameOver.h"
#include "glew.h"
#include <iostream>
#include "ResourceLoader.h"

const std::string GameOver::stateID = "GAMEOVER";

bool GameOver::OnEnter()
{
	std::cout << "Entering GameOver!\n";
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 413 }, Size{ 256.0f, 68.0f }, "REPLAY", std::make_unique<ReplayCommand>()));
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 313 }, Size{ 256.0f, 68.0f }, "QUIT", std::make_unique<QuitCommand>()));

	background = std::make_unique<Image>(0.0f, 0.0f, 1280.0f, 720.0f, ResourceLoader::textures[TEXTURE::UI_BACKGROUND]);

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

	background->Render();

	for (const auto& button : buttons) {
		button->Render();
	}
}
