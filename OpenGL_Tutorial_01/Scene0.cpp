#include "Scene0.h"
#include "SDL.h"
#include "DemoObject.h"
#include "OBJLoader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Scene0::Scene0(): monkey(nullptr), mesh(nullptr), tex(nullptr), shader(nullptr){
	Create();
}

Scene0::~Scene0(){
	if (monkey) delete monkey, monkey = nullptr;
	if (mesh) delete mesh, mesh = nullptr;
	if (tex) delete tex, tex = nullptr;
	if (shader) delete shader, shader = nullptr;
}

void Scene0::Create() {
	//SHADERS//////////////////////////////////////////////////
	shader = new Shader("VertShader.vert", "FragShader.frag");

	//MODELS//////////////////////////////////////////////////
	if (OBJLoader::loadOBJ("Resources\\Models\\monkey.obj")) {
		mesh = new Mesh(OBJLoader::vertices, OBJLoader::uvs);

		tex = new Texture();
		tex->loadTexture("Resources\\Art\\grass_01.png");

		if (!shader || !tex || !mesh)
			std::cout << "ERROR: Resources failed to build!" << std::endl;

		monkey = new DemoObject(mesh, shader, tex);

		if (!monkey)
			std::cout << "ERROR: Monkey object failed to build!" << std::endl;
	}

	//Transforms
	modelM = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, -10.0f }) *
			 glm::rotate(glm::mat4{ 1.0f }, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	viewM = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f });

	auto projM = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	auto mvp = projM * viewM * modelM;

	shader->useProgram();
	//Projection matrix rarely changes it's best to set it only once
	int mvpLoc = glGetUniformLocation(shader->getShaderID(), "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

}

void Scene0::HandleEvents(const SDL_Event &ev) {}

void Scene0::Update(float deltatime) {
	monkey->Update(deltatime);
}

void Scene0::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	monkey->Render();
}