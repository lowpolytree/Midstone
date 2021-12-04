#pragma once
#include "Level.h"
#include <vector>
#include <memory>
#include "Image.h"

class Menu : public Level
{
public:

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

