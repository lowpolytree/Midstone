#pragma once
#include "Observable.h"
#include "glm/matrix.hpp"
#include <memory>
#include <string>
#include "Text.h"
#include "Command.h"

union SDL_Event;

struct Size {
	float width;
	float height;
};

struct Position {
	float x;
	float y;
};

enum class STATE {
	DEFAULT,
	PRESSED,
	HOVER,
};

class Button
{
public:
	Button(Position p, Size s, const std::string& buttonText_, std::unique_ptr<Command>&& cmd);

	void OnCreate();
	void HandleEvents(const SDL_Event& ev);
	void Render();

	auto GetState() const { return state; }

	void ExecuteCommand() { buttonCommand->Execute(); }

	auto getIsActive() const { return isActive; }
	void setIsActive(bool status) { isActive = status; }

private:
	Size size;
	Position position;
	int mouseX, mouseY;
	float minX, minY, maxX, maxY;
	
	unsigned int VAO, VBO, EBO;
	glm::mat4 model;
	glm::mat4 projection;

	std::string buttonText;
	std::unique_ptr<Text> text;
	
	STATE state;
	bool isActive;
	std::unique_ptr<Command> buttonCommand;
};

