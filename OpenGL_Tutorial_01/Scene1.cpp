#include "Scene1.h"
#include "SDL.h"
#include <random>
#include <chrono>

#include "DemoObject.h"
#include "OBJLoader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr float PI = 3.14159265359f;

Scene1::Scene1(): monkey(nullptr), mesh(nullptr), tex(nullptr), shader(nullptr){
	tempdeltatime = 0.0f;
	Create();
}

Scene1::~Scene1(){
	if (monkey) delete monkey, monkey = nullptr;
	if (mesh) delete mesh, mesh = nullptr;
	if (tex) delete tex, tex = nullptr;
	if (shader) delete shader, shader = nullptr;
}

void Scene1::Create() {
	//RANDOM STUFF
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine r(seed);
	float minX = -6.0f;
	float maxX =  6.0f;
	float minY = -3.0f;
	float maxY =  3.0f;
	float minScale = 0.3f;

	float maxScale = 1.0f;
	float minAngle = 0.0f;
	float maxAngle = 2.0f * PI;

	//SHADERS//////////////////////////////////////////////////
	shader = new Shader("InstancedVertShader.vert", "InstancedFragShader.frag");

	//MODELS//////////////////////////////////////////////////
	if (OBJLoader::loadOBJ("Resources\\Models\\monkey.obj")) {
		mesh = new Mesh(OBJLoader::vertices, OBJLoader::uvs);

		tex = new Texture();
		tex->loadTexture("Resources\\Art\\tex_monkey.png");

		if (!shader || !tex || !mesh)
			std::cout << "ERROR: Resources failed to build!" << std::endl;

		monkey = new DemoObject(mesh, shader, tex);

		if (!monkey)
			std::cout << "ERROR: Monkey object failed to build!" << std::endl;
	}

	//Transforms
	modelM = new glm::mat4[10];

	for (int i = 0; i < 10; i++) {

		float randomX = std::uniform_real_distribution<>{ minX, maxX }(r);
		float randomY = std::uniform_real_distribution<>{ minY, maxY }(r);
		float randomScale = std::uniform_real_distribution<>{ minScale, maxScale }(r);
		float randomAngle = std::uniform_real_distribution<>{ minAngle, maxAngle }(r);

		std::cout << "RandomX: " << randomX << ", RandomY: " << randomY << ", Random Scale: " << randomScale << "\n";
		glm::mat4 model = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ randomX, randomY, -10.0f });
		model = glm::rotate(model, randomAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		model =	glm::scale(model, glm::vec3{ randomScale });

		modelM[i] = model;
	}

	viewM = glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f });

	auto projM = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	shader->useProgram();
	//Projection matrix rarely changes it's best to set it only once
	int projLoc = glGetUniformLocation(shader->getShaderID(), "projM");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projM));

	int viewLoc = glGetUniformLocation(shader->getShaderID(), "viewM");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewM));

	//Pass an array of model matrices to vertex shader
	for (int i = 0; i < 30; i++) {
		std::string varName = "modelM[" + std::to_string(i) + "]";
		int modelLoc = glGetUniformLocation(shader->getShaderID(), varName.c_str());
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM[i]));
	}
}

void Scene1::HandleEvents(const SDL_Event &ev) {}

void Scene1::Update(float deltatime) {
	monkey->Update(deltatime);

	tempdeltatime += deltatime;
}

void Scene1::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->useProgram();

	int deltatimeLoc = glGetUniformLocation(shader->getShaderID(), "deltatime");
	glUniform1f(deltatimeLoc, tempdeltatime);
	monkey->Render();
}