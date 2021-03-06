#include "Level2.h"
#include "LevelManager.h"
#include "SDL.h"
#include "DemoObject.h"
#include "ResourceLoader.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Map.h"
#include "Player.h"
#include "Collisions.h"
#include "Tile.h"
#include "Text.h"
#include "Fire.h"

const std::string Level2::stateID = "LEVEL2";

Level2::Level2(){}

bool Level2::OnEnter() {
	std::cout << "Entering Level2!\n";
	//RESOURCES ARE LOADED IN THE MENU

	//LIGHTS////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Directional light
	auto dirLightModelM = glm::rotate(glm::mat4{ 1.0f }, 0.0f, glm::vec3{ 1.0f, 0.0f, 0.0f });
	ResourceLoader::shaders[SHADER::LAMBERT]->sendMatrixToShader("dirLightModelM", dirLightModelM);
	ResourceLoader::shaders[SHADER::TILE]->sendMatrixToShader("dirLightModelM", dirLightModelM);

	//MAPS//////////////////////////////////////////////////////////////////////////////////////////////////////////
	map = std::make_unique<Map>();
	if (!map->Load("Resources\\Maps\\Level2.txt", ResourceLoader::meshes, ResourceLoader::shaders[SHADER::TILE], ResourceLoader::textures[TEXTURE::PALETTE])) {
		return false;
	}

	//SETTING UP MAPS
	map->generateTilePositions();
	map->setTilePositions();
	map->setTileModelM();

	//ENVIRONMENT ASSETS
	//GROUND
	ground = std::make_unique<DemoObject>(ResourceLoader::meshes[MESH::GROUND2], ResourceLoader::shaders[SHADER::LAMBERT], ResourceLoader::textures[TEXTURE::PALETTE]);
	ground->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }));
	ground->setNormalMatrix(glm::transpose(glm::inverse(ground->getModelMatrix())));

	//FIRE
	fire = std::make_unique<Fire>();
	fire->Load(ResourceLoader::meshes[MESH::FLAME], ResourceLoader::shaders[SHADER::FIRE], ResourceLoader::textures[TEXTURE::PALETTE]);
	fire->SetPosition(glm::vec3{ 16.0f, 0.8f, 0.3f });

	//PLAYER////////////////////////////////////////////////////////////////////////////////////////////////////////
	player = std::make_unique<Player>();
	if (!player->Load(ResourceLoader::meshes[MESH::PLAYER], ResourceLoader::shaders[SHADER::LAMBERT], ResourceLoader::textures[TEXTURE::PALETTE]))
		return false;
	player->setPositon(map->getStartingPosition());
	player->getPlayerObject()->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, player->getPosition()));
	player->getPlayerObject()->setNormalMatrix(glm::transpose(glm::inverse(player->getPlayerObject()->getModelMatrix())));

	//CAMERA/////////////////////////////////////////////////
	auto mapMidPoint = 6.0f;
	auto cameraHeight = 20.0f;
	auto cameraOffset = 13.5f;
	camera = std::make_unique<Camera>();
	camera->SetUpCamera(mapMidPoint, cameraHeight, cameraOffset);

	//VIEW AND PROJ MATRIX TO SHADER
	ResourceLoader::shaders[SHADER::LAMBERT]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders[SHADER::LAMBERT]->sendMatrixToShader("projM", camera->getProjMatrix());

	ResourceLoader::shaders[SHADER::TILE]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders[SHADER::TILE]->sendMatrixToShader("projM", camera->getProjMatrix());

	ResourceLoader::shaders[SHADER::AABB]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders[SHADER::AABB]->sendMatrixToShader("projM", camera->getProjMatrix());

	return true;
}

bool Level2::OnExit()
{
	std::cout << "Exiting Level2!\n";
	return true;
}

void Level2::HandleEvents(const SDL_Event &ev) {
	player->HandleEvents(ev);

	if (ev.type == SDL_KEYDOWN) {
		
		if (ev.type == SDL_KEYDOWN) {
			switch (ev.key.keysym.sym) {
			case SDLK_UP:
				player->Move(map.get(), glm::vec3{ 0.0f, 0.0f, -1.0f });
				//MovePlayer(glm::vec3{ 0.0f, 0.0f, -1.0f }); // UP
				break;
			case SDLK_DOWN:
				player->Move(map.get(), glm::vec3{ 0.0f, 0.0f, 1.0f });
				//MovePlayer(glm::vec3{ 0.0f, 0.0f, 1.0f });  // DOWN
				break;
			case SDLK_LEFT:
				player->Move(map.get(), glm::vec3{ -1.0f, 0.0f, 0.0f });
				//MovePlayer(glm::vec3{ -1.0f, 0.0f, 0.0f }); // LEFT
				break;
			case SDLK_RIGHT:
				player->Move(map.get(), glm::vec3{ 1.0f, 0.0f, 0.0f });
				//MovePlayer(glm::vec3{ 1.0f, 0.0f, 0.0f });  // RIGHt
				break;
			default: 
				break;
			}
		}
	}
}

void Level2::Update(float deltatime) {
	player->Update(deltatime);
	fire->Update(deltatime);

	for (const auto& tile : map->getTiles()) {

		if (Collisions::Intersection(*player->getAABB(), player->getPosition(), *tile->getAABB(), tile->getPosition())) {
			tile->setIsIntersecting(true);
		}
		else {
			tile->setIsIntersecting(false);
		}

		if (map->checkIfAllTilesTraversed()) {
			if (map->checkMapForWin()) {
				std::cout << "You win the game!\n";
				LevelManager::levelCounter++;
				LevelManager::LoadLevel(Scene::LEVEL);
				break;
			}
			else {
				std::cout << "You lost the game!\n";
				LevelManager::LoadLevel(Scene::GAME_OVER);
				break;
			}
		}

		if (map->checkMapForLose()) {
			std::cout << "You lost the game!\n";
			LevelManager::LoadLevel(Scene::GAME_OVER);
			break;
		}
	}
}

void Level2::Render() {

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ground->Render();
	map->Render();
	player->Render();
	fire->Render();
}

