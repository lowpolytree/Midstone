#include "LevelTest.h"
#include "SDL.h"
#include "DemoObject.h"
#include "ResourceLoader.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Fire.h"

LevelTest::LevelTest(){
	tempdeltatime = 0.0f;
}

bool LevelTest::OnEnter()
{
	//RESOURCES/////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!ResourceLoader::LoadResources()) {
		std::cout << "ERROR: Resources failed to load!\n";
		false;
	}

	//CAMERA/////////////////////////////////////////////////
	auto mapMidPoint = 0.0f;
	auto cameraHeight = 0.0f;
	auto cameraOffset = 10.0f;
	camera = std::make_unique<Camera>();
	camera->SetUpCamera(mapMidPoint, cameraHeight, cameraOffset);

	//VIEW AND PROJ MATRIX TO SHADER
	ResourceLoader::shaders[SHADER::FIRE]->sendMatrixToShader("viewM", camera->getViewMatrix());
	ResourceLoader::shaders[SHADER::FIRE]->sendMatrixToShader("projM", camera->getProjMatrix());

	fire = std::make_unique<Fire>();
	fire->Load(ResourceLoader::meshes[MESH::FLAME], ResourceLoader::shaders[SHADER::FIRE], ResourceLoader::textures[TEXTURE::PALETTE]);

	return true;
}

bool LevelTest::OnExit()
{
	return false;
}

void LevelTest::HandleEvents(const SDL_Event &ev) {}

void LevelTest::Update(float deltatime) {
	fire->Update(deltatime);
}

void LevelTest::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	fire->Render();

}