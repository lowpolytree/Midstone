#include "Scene2.h"
#include "SDL.h"
#include <chrono>

#include "DemoObject.h"
#include "OBJLoader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr float PI = 3.14159265359f;

Scene2::Scene2(): monkey(nullptr), monkey1(nullptr), monkey2(nullptr), mesh(nullptr), tex(nullptr), shader(nullptr){
	tempdeltatime = 0.0f;
	Create();
}

Scene2::~Scene2(){
	if (monkey) delete monkey, monkey = nullptr;
	if (monkey1) delete monkey1, monkey1 = nullptr;
	if (monkey2) delete monkey2, monkey2 = nullptr;
	if (mesh) delete mesh, mesh = nullptr;
	if (tex) delete tex, tex = nullptr;
	if (shader) delete shader, shader = nullptr;
}

void Scene2::Create() {
	//unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	
	//SHADERS//////////////////////////////////////////////////
	shader = new Shader("VertShader.vert", "FragShader.frag");

	//MODELS//////////////////////////////////////////////////
	if (OBJLoader::loadOBJ("Resources\\Models\\monkey.obj")) {
		mesh = new Mesh(OBJLoader::vertices, OBJLoader::uvs);

		tex = new Texture();
		tex->loadTexture("Resources\\Art\\tex_monkey.png");

		if (!shader || !tex || !mesh)
			std::cout << "ERROR: Resources failed to build!" << std::endl;

		monkey = new DemoObject(mesh, shader, tex);
		monkey1 = new DemoObject(mesh, shader, tex);
		monkey2 = new DemoObject(mesh, shader, tex);

		if (!monkey && !monkey1 && !monkey2)
			std::cout << "ERROR: Monkey object failed to build!" << std::endl;
	}

	//TRANSFORMS

	//Projection matrix for monkey 1
	monkey->getShader()->useProgram();
	projM = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	int projLoc = glGetUniformLocation(monkey->getShader()->getShaderID(), "projM");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projM));

	//Projection matrix for monkey 2
	monkey1->getShader()->useProgram();
	projLoc = glGetUniformLocation(monkey1->getShader()->getShaderID(), "projM");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projM));

	//Projection matrix for monkey 3
	monkey2->getShader()->useProgram();
	projLoc = glGetUniformLocation(monkey2->getShader()->getShaderID(), "projM");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projM));

}

void Scene2::HandleEvents(const SDL_Event &ev) {}

void Scene2::Update(float deltatime) {
	tempdeltatime += deltatime;
	//std::cout << tempdeltatime << "\n";
}

void Scene2::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Transforms
	//The VIEW matrix
	mvStack.push(glm::mat4{ 1.0f });
	mvStack.top() *= glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f });

	//First monkey mv matrix
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, -10.0f });
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4{ 1.0f }, tempdeltatime * 0.2f, glm::vec3(0.0f, 1.0f, 0.0f));

	monkey->getShader()->useProgram();
	int modelLoc = glGetUniformLocation(monkey->getShader()->getShaderID(), "mvM");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

	//Draw first monkey
	monkey->Render();

	mvStack.pop(); //deleting rotation matrix


	//Second monkey mv matrix
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4{ 1.0f }, glm::vec3{ sin(tempdeltatime * 0.5f) * 3.0f, 0.0f, cos(tempdeltatime * 0.5f) * 3.0f });

	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4{ 1.0f }, tempdeltatime * -0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
	mvStack.top() *= glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 0.5f });

	monkey1->getShader()->useProgram();
	modelLoc = glGetUniformLocation(monkey1->getShader()->getShaderID(), "mvM");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

	monkey1->Render();
	mvStack.pop(); //deleting rotation matrix

	//Third monkey mv matrix
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, sin(tempdeltatime), cos(tempdeltatime) });
	mvStack.top() *= glm::rotate(glm::mat4{ 1.0f }, tempdeltatime * -0.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	mvStack.top() *= glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 0.2f });

	monkey2->getShader()->useProgram();
	modelLoc = glGetUniformLocation(monkey2->getShader()->getShaderID(), "mvM");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

	monkey2->Render();

	//mvStack.pop();
	mvStack.pop(); 
	mvStack.pop();
	mvStack.pop();
}