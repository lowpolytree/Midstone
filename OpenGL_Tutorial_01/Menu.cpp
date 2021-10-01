#include "Menu.h"
#include "glew.h"
#include <iostream>
#include "Command.h"
#include "Button.h"

const std::string Menu::stateID = "MENU";

bool Menu::OnEnter()
{
	std::cout << "Entering Menu!\n";
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 500 }, Size{ 256.0f, 68.0f }, "PLAY", std::make_unique<PlayCommand>()));
	buttons.push_back(std::make_shared<Button>(Position{ 1280 / 2, 400 }, Size{ 256.0f, 68.0f }, "QUIT", std::make_unique<QuitCommand>()));

	return true;
}

bool Menu::OnExit()
{
	std::cout << "Exiting Menu!\n";
	return true;
}

void Menu::HandleEvents(const SDL_Event& ev) {
	for (const auto& button : buttons) {
		if (!button->getIsActive()) break;
		button->HandleEvents(ev);
	}
}

void Menu::Update(float deltatime) {}

void Menu::Render() {

	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto& button : buttons) {
		button->Render();
	}
}
