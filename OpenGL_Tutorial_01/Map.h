#pragma once
#include "DemoObject.h"
#include <memory>
#include <vector>
#include <string>
#include "Observable.h"
#include "CollisionObserver.h"

class Map
{
public:
	Map();
	~Map();

	bool Load(const std::shared_ptr<class Mesh>& mesh, const std::shared_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& tex);
	void Render();

	//Functionality
	void setTileModelM() const;
	void generateTilePositions();
	void setTilePositions();
	auto& getTiles() const { return tiles; }

	glm::vec3 getStartingPosition();

	bool checkMapForWin() const;
	bool checkIfAllTilesTraversed() const;
	bool checkMapForLose() const;

private:
	std::vector<std::unique_ptr<class Tile>> tiles;
	std::vector<glm::vec3> positions;

	int MAP_WIDTH;

	CollisionObserver collisionObserver;
};

