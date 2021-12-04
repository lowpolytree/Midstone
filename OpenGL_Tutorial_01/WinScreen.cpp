#include "WinScreen.h"
#include "glew.h"
#include <iostream>
#include "ResourceLoader.h"

const std::string WinScreen::stateID = "GAMEOVER";

bool WinScreen::OnEnter()
{
	std::cout << "Entering WinScreen!\n";
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 250 }, Size{ 256.0f, 68.0f }, "TO MENU", std::make_unique<ToMenuCommand>()));
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 150 }, Size{ 256.0f, 68.0f }, "QUIT", std::make_unique<QuitCommand>()));

	background = std::make_unique<Image>(0.0f, 0.0f, 1280.0f, 720.0f, ResourceLoader::textures[TEXTURE::UI_WIN]);

	return true;
}

bool WinScreen::OnExit()
{
	std::cout << "Exiting WinScreen!\n";
	return true;
}

void WinScreen::HandleEvents(const SDL_Event& ev) {
	for (const auto& button : buttons) {
		if (!button->getIsActive()) break;
		button->HandleEvents(ev);
	}
}

void WinScreen::Update(float deltatime) {}

void WinScreen::Render() {

	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	background->Render();

	for (const auto& button : buttons) {
		button->Render();
	}
}
