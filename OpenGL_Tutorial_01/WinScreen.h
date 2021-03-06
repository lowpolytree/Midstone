#pragma once
#include "Level.h"
#include <memory>
#include "Button.h"
#include "Image.h"

class WinScreen : public Level
{
	bool OnEnter() override;
	bool OnExit() override;

	void HandleEvents(const SDL_Event& ev) override;
	void Update(float deltatime) override;
	void Render() override;

	virtual std::string getStateID() const override { return stateID; }

private:
	static const std::string stateID;

	std::vector<std::shared_ptr<class Button>> buttons;
	std::unique_ptr<Image> background;
};

