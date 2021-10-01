#include "Scene3.h"
#include "SDL.h"
#include <chrono>
#include "DemoObject.h"
#include "OBJLoader.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

constexpr float PI = 3.14159265359f;

Scene3::Scene3(){
	tempdeltatime = 0.0f;
	if(!Create()) std::cout << "ERROR: Scene::Create() failed!\n";
}

Scene3::~Scene3(){}

bool Scene3::Create() {
	//SHADERS//////////////////////////////////////////////////
	shader = std::make_shared<Shader>("BlinnPhongShader.vert", "BlinnPhongShader.frag");

	//MODELS//////////////////////////////////////////////////
	//MESH///////////////////////////////////////////////////
	if (!OBJLoader::loadOBJ("Resources\\Models\\monkey_smooth.obj"))
		return false;
	monkeyMesh = std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals);

	//TEXTURES///////////////////////////////////////////////
	monkeyTex = std::make_shared <Texture>();
	monkeyTex->loadTexture("Resources\\Art\\tex_monkey.png");

	planeTex = std::make_shared <Texture>();
	planeTex->loadTexture("Resources\\Art\\grass_01.png");


	//DEMOOBJECTS////////////////////////////////////////////
	monkey = std::make_unique <DemoObject>(monkeyMesh, shader, monkeyTex);


	if (!OBJLoader::loadOBJ("Resources\\Models\\plane.obj"))
		return false;
	planeMesh = std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals);

	plane = std::make_unique <DemoObject>(planeMesh, shader, planeTex);

	if (!shader || !monkeyMesh || !monkeyTex || !planeMesh || !planeTex)
		std::cout << "ERROR: Resources failed to build!" << std::endl;

	if (!monkey || !plane)
		std::cout << "ERROR:  A game bject failed to build!" << std::endl;

	//CAMERA/////////////////////////////////////////////////
	camera = std::make_unique<Camera>();
	camera->setProjMatrix(glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
	camera->setViewMatrix(glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, -10.0f }));

	//MODEL MATRIX///////////////////////////////////////////
	monkey->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }));
	plane->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f }));

	//PROJECTION/////////////////////////////////////////////
	camera->sendProjToShader(monkey->getShader(), "projM");
	//camera->sendProjToShader(plane->getShader(), "projM");

	//LIGHTS/////////////////////////////////////////////////
	glm::vec3 light1{ 2.0f, 2.0f, 2.0f };
	monkey->sendVec3ToShader("lightPos", light1);
	//plane->sendVec3ToShader("lightPos", light1); // optional

	return true;
}

void Scene3::HandleEvents(const SDL_Event &ev) {}

void Scene3::Update(float deltatime) {
	tempdeltatime += deltatime;
	//std::cout << tempdeltatime << "\n";
}

void Scene3::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Use shader
	monkey->getShader()->useProgram();
	//Construct model matrix
	monkey->setModelMatrix(glm::rotate(glm::mat4{ 1.0f }, tempdeltatime, glm::vec3{ 0.0f, 1.0f, 0.0f }));
	
	//Construct MV matrix and pass it to shader
	auto mv = camera->getViewMatrix() * monkey->getModelMatrix();
	monkey->sendMat4ToShader("mvM", mv);

	//Construct normal matrix and pass it to shader
	//Normal matrix is transpose inverse of model view matrix
	//Normal matrix is in eye/view space
	auto normM = glm::transpose(glm::inverse(mv));
	monkey->sendMat4ToShader("normM", normM);

	monkey->Render();

	//PLANE////////////////////////////////////////////////////////////////////
	//MV MATRIX
	mv = camera->getViewMatrix() * plane->getModelMatrix();
	plane->sendMat4ToShader("mvM", mv);
	//NORMAL MATRIX
	normM = glm::transpose(glm::inverse(mv));
	plane->sendMat4ToShader("normM", normM);

	plane->Render();
}