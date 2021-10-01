#include "LevelTest.h"
#include "SDL.h"
#include "DemoObject.h"
#include "ResourceLoader.h"
#include "Collisions.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Map.h"
#include "Player.h"

LevelTest::LevelTest(){
	tempdeltatime = 0.0f;
	if(!Create()) std::cout << "ERROR: Level::Create() failed!\n";
}

LevelTest::~LevelTest(){}

bool LevelTest::Create() {
	//RESOURCES/////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!ResourceLoader::LoadResources()) {
		std::cout << "ERROR: Resources failed to load!\n";
		false;
	}

	//CAMERA/////////////////////////////////////////////////
	camera = std::make_unique<Camera>();
	camera->setProjMatrix(glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
	camera->setViewMatrix(glm::lookAt(glm::vec3{ 6.0f, 10.0f, 10.0f }, glm::vec3{6.0f, 0.0f, -6.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f }));
	
	//VIEW AND PROJ MATRIX TO SHADER
	ResourceLoader::shaders["lambert"]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders["lambert"]->sendMatrixToShader("projM", camera->getProjMatrix());

	ResourceLoader::shaders["aabb"]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders["aabb"]->sendMatrixToShader("projM", camera->getProjMatrix());

	//LIGHTS////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Directional light
	auto dirLightModelM = glm::rotate(glm::mat4{ 1.0f }, 0.0f, glm::vec3{ 1.0f, 0.0f, 0.0f });
	ResourceLoader::shaders["lambert"]->sendMatrixToShader("dirLightModelM", dirLightModelM);

	//PLAYER////////////////////////////////////////////////////////////////////////////////////////////////////////
	player = std::make_unique<Player>();
	if (!player->Load(ResourceLoader::meshes["player"], ResourceLoader::shaders["lambert"], ResourceLoader::textures["palette"]))
		return false;
	player->setPositon(glm::vec3{ 0.0f });
	player->getPlayerObject()->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, player->getPosition()));
	player->getPlayerObject()->setNormalMatrix(glm::transpose(glm::inverse(player->getPlayerObject()->getModelMatrix())));


	player1 = std::make_unique<Player>();
	if (!player1->Load(ResourceLoader::meshes["player"], ResourceLoader::shaders["lambert"], ResourceLoader::textures["palette"]))
		return false;
	player1->setPositon(glm::vec3{ 4.0f, 0.0f, -4.0f });
	player1->getPlayerObject()->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, player1->getPosition()));
	player1->getPlayerObject()->setNormalMatrix(glm::transpose(glm::inverse(player1->getPlayerObject()->getModelMatrix())));

	return true;
}

void LevelTest::HandleEvents(const SDL_Event &ev) {
	player->HandleEvents(ev);
	//player1->HandleEvents(ev);
}

void LevelTest::Update(float deltatime) {
	player->Update();
	player1->Update();
	//tempdeltatime += deltatime;

	if (Collisions::Intersection(*player->getAABB(), player->getPosition(), *player1->getAABB(), player1->getPosition())) {
		std::cout << "There is a collision!\n";
	}
}

void LevelTest::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player->Render();
	player1->Render();
}