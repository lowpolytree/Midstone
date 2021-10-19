#pragma once

enum class Scene {
	MENU,
	GAME_OVER,
	LEVEL,
};

class LevelManager
{
public:
	static void LoadLevel(const Scene type);
	static int levelCounter;
private:
};

