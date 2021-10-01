#include "Level0.h"
#include "Game.h"
#include "GameOver.h"
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

const std::string Level0::stateID = "LEVEL0";

Level0::Level0(){}

bool Level0::OnEnter() {
	std::cout << "Entering Level0!\n";
	//RESOURCES ARE LOADED IN THE MENU

	//CAMERA/////////////////////////////////////////////////
	camera = std::make_unique<Camera>();
	camera->setProjMatrix(glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
	camera->setViewMatrix(glm::lookAt(glm::vec3{ 6.0f, 20.0f, 10.0f }, glm::vec3{6.0f, 0.0f, -6.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f }));
	

	//VIEW AND PROJ MATRIX TO SHADER
	ResourceLoader::shaders[SHADER::LAMBERT]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders[SHADER::LAMBERT]->sendMatrixToShader("projM", camera->getProjMatrix());

	ResourceLoader::shaders[SHADER::TILE]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders[SHADER::TILE]->sendMatrixToShader("projM", camera->getProjMatrix());

	ResourceLoader::shaders[SHADER::AABB]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders[SHADER::AABB]->sendMatrixToShader("projM", camera->getProjMatrix());

	//LIGHTS////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Directional light
	auto dirLightModelM = glm::rotate(glm::mat4{ 1.0f }, 0.0f, glm::vec3{ 1.0f, 0.0f, 0.0f });
	ResourceLoader::shaders[SHADER::LAMBERT]->sendMatrixToShader("dirLightModelM", dirLightModelM);
	ResourceLoader::shaders[SHADER::TILE]->sendMatrixToShader("dirLightModelM", dirLightModelM);

	//MAPS//////////////////////////////////////////////////////////////////////////////////////////////////////////
	map = std::make_unique<Map>();
	if (!map->Load(ResourceLoader::meshes[MESH::TILE], ResourceLoader::shaders[SHADER::TILE], ResourceLoader::textures[TEXTURE::PALETTE])) {
		return false;
	}

	//SETTING UP MAPS
	map->generateTilePositions();
	map->setTilePositions();
	map->setTileModelM();

	//ENVIRONMENT ASSETS
	//GROUND
	ground = std::make_unique<DemoObject>(ResourceLoader::meshes[MESH::GROUND], ResourceLoader::shaders[SHADER::LAMBERT], ResourceLoader::textures[TEXTURE::PALETTE]);
	ground->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 6.0f, 0.0f, -6.0f }));
	ground->setNormalMatrix(glm::transpose(glm::inverse(ground->getModelMatrix())));

	//PLAYER////////////////////////////////////////////////////////////////////////////////////////////////////////
	player = std::make_unique<Player>();
	if (!player->Load(ResourceLoader::meshes[MESH::PLAYER], ResourceLoader::shaders[SHADER::LAMBERT], ResourceLoader::textures[TEXTURE::PALETTE]))
		return false;
	player->setPositon(map->getStartingPosition());
	player->getPlayerObject()->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, player->getPosition()));
	player->getPlayerObject()->setNormalMatrix(glm::transpose(glm::inverse(player->getPlayerObject()->getModelMatrix())));

	return true;
}

bool Level0::OnExit()
{
	std::cout << "Exiting Level0!\n";
	return true;
}

void Level0::HandleEvents(const SDL_Event &ev) {
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

void Level0::Update(float deltatime) {
	player->Update(deltatime);

	for (const auto& tile : map->getTiles()) {

		if (Collisions::Intersection(*player->getAABB(), player->getPosition(), *tile->getAABB(), tile->getPosition())) {
			tile->setIsIntersecting(true);
		}
		else {
			tile->setIsIntersecting(false);
		}

		if (map->checkMapForLose()) {
			std::cout << "You lost the game!\n";
			Game::gameStateMachine->ChangeLevel(new GameOver());
			break;
		}

		if (map->checkIfAllTilesTraversed()) {
			if (map->checkMapForWin()) {
				std::cout << "You win the game!\n";
				Game::gameStateMachine->ChangeLevel(new GameOver());
				break;
			}
			else {
				std::cout << "You lost the game!\n";
				Game::gameStateMachine->ChangeLevel(new GameOver());
				break;
			}
		}
	}
}

void Level0::Render() {

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ground->Render();
	map->Render();
	player->Render();
}

