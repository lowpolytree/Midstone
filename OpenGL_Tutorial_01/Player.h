#pragma once
#include <memory>
#include <glm/vec3.hpp>

union SDL_Event;

class Player
{
public:
	Player();
	~Player();

	bool Load(const std::shared_ptr<class Mesh>& mesh, const std::shared_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& tex);
	void Update(const float deltatime);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);

	void Move(class Map* map, const glm::vec3& direction);

	auto& getPlayerObject() const { return player; }
	auto& getAABB() const { return aabb; }

	void setPositon(const glm::vec3& pos) { position = pos; }
	auto& getPosition() const { return position; }

	void setNextPosition(const glm::vec3& pos) { nextPosition = pos; }
	auto& getNextPosition() const { return nextPosition; }

	void setOldPosition(const glm::vec3& pos) { oldPosition = pos; }
	auto& getOldPosition() const { return oldPosition; }

	void setIsMoving(bool status) { isMoving = status; }
	bool getIsMoving() const { return isMoving; }

private:
	std::unique_ptr<class DemoObject> player;
	std::unique_ptr<class AABB> aabb;
	glm::vec3 position;
	glm::vec3 nextPosition;
	glm::vec3 oldPosition;
	bool isMoving;
	float timer;
	float rotTimer;
};

