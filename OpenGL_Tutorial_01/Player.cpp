#include "Player.h"
#include <SDL.h>
#include "DemoObject.h"
#include "AABB.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Utilities.h"
#include "Collisions.h"
#include "Map.h"
#include "Tile.h"

Player::Player(): isMoving(false), timer(0.0f), rotTimer(0.0f) {}

Player::~Player() {}

bool Player::Load(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& tex) {
	isMoving = false;
	timer = 0;
	player = std::make_unique<DemoObject>(mesh, shader, tex);

	if (!player) {
		std::cout << "ERROR: Player failed to load!\n";
		return false;
	}

	//AABB
	aabb = std::make_unique<AABB>();
	if(!aabb->Construct(player->getMesh())) {
		std::cout << "ERROR: Player AABB failed to construct!\n";
		return false;
	}

	return true;
}

void Player::Update(const float deltatime) {

	//Rotates player
	if (rotTimer > 1.0f)
		rotTimer = 0.0f;

	auto rotationAngle = glm::mix(0.0f, 360.0f, rotTimer);

	rotTimer += deltatime * 0.005f;
	
	player->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, position) * glm::rotate(glm::mat4{ 1.0f }, rotationAngle, glm::vec3{ 0.0f, 1.0f, 0.0f }));
	aabb->setParentModelMatrix(player->getModelMatrix());

	//std::cout << deltatime << "\n";

	//Moving from on tile to another
	//Lerp for smooth transition
	if (!isMoving) return;

	position = Utilities::Lerp(oldPosition, nextPosition, timer);
	timer += deltatime;

	if (timer >= 1.0f) {
		isMoving = false;
		timer = 0;
	}
}

void Player::Render() {
	player->Render();
	aabb->Render();
}

void Player::HandleEvents(const SDL_Event& sdlEvent){
	
}

void Player::Move(Map* map, const glm::vec3& direction)
{
	if (isMoving) return;

	Ray rayFromPlayer{ position, direction };

	for (const auto& tile : map->getTiles()) {

		if (tile->getIsIntersecting() == true || tile->getIsBlock() == true)
			continue;

		if (Collisions::Intersection(rayFromPlayer, *tile->getAABB(), tile->getPosition())) {
			std::cout << "Intersection detected with tile at " << tile->getPosition().x << ", " << tile->getPosition().z << "\n";
			setNextPosition(tile->getPosition());
			setOldPosition(position);
			setIsMoving(true);
			break;
		}
	}
}
