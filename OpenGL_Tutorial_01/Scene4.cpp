#include "Scene4.h"
#include "SDL.h"
#include <chrono>
#include "Game.h"
#include "DemoObject.h"
#include "OBJLoader.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

//constexpr float PI = 3.14159265359f;

Scene4::Scene4(){
	tempdeltatime = 0.0f;
	if(!Create()) std::cout << "ERROR: Scene::Create() failed!\n";
}

Scene4::~Scene4(){}

bool Scene4::Create() {
	//SHADERS//////////////////////////////////////////////////
	//shader = std::make_shared<Shader>("BlinnPhongShader.vert", "BlinnPhongShader.frag");
	
	shadowPass1Shader = std::make_shared<Shader>("ShadowsBPShader_PassOne.vert", "ShadowsBPShader_PassOne.frag");
	shadowPass2Shader = std::make_shared<Shader>("ShadowsBPShader_PassTwo.vert", "ShadowsBPShader_PassTwo.frag");

	//MODELS//////////////////////////////////////////////////
	//MESH///////////////////////////////////////////////////
	if (!OBJLoader::loadOBJ("Resources\\Models\\cube.obj"))
		return false;
	monkeyMesh = std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals);

	//TEXTURES///////////////////////////////////////////////
	monkeyTex = std::make_shared <Texture>();
	monkeyTex->loadTexture("Resources\\Art\\grass_01.png");

	planeTex = std::make_shared <Texture>();
	planeTex->loadTexture("Resources\\Art\\grass_01.png");


	//DEMOOBJECTS////////////////////////////////////////////
	monkey = std::make_unique <DemoObject>(monkeyMesh, shadowPass2Shader, monkeyTex);


	if (!OBJLoader::loadOBJ("Resources\\Models\\plane.obj"))
		return false;
	planeMesh = std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals);

	plane = std::make_unique <DemoObject>(planeMesh, shadowPass2Shader, planeTex);

	if (!monkeyMesh || !monkeyTex || !planeMesh || !planeTex)
		std::cout << "ERROR: Resources failed to build!" << std::endl;

	if (!monkey || !plane)
		std::cout << "ERROR:  A game bject failed to build!" << std::endl;

	//CAMERA/////////////////////////////////////////////////
	camera = std::make_unique<Camera>();
	camera->setProjMatrix(glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
	camera->setViewMatrix(glm::lookAt(glm::vec3{ 0.0f, 5.0f, 15.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f }));

	//BIAS MATRIX
	biasMatrix = glm::mat4{
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	};

	//MODEL MATRIX///////////////////////////////////////////
	monkey->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }));
	plane->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f }));

	//PROJECTION/////////////////////////////////////////////
	camera->sendProjToShader(monkey->getShader(), "projM");

	//LIGHTS/////////////////////////////////////////////////
	glm::vec3 light1{ 2.0f, 2.0f, 2.0f };
	monkey->sendVec3ToShader("lightPos", light1);

	//SHADOW BUFFER
	int width, height;
	SDL_GetWindowSize(Game::win, &width, &height);
	
	//Creating a FBO
	glGenFramebuffers(1, &shadowBuffer);
	
	//Creating a shadow texture
	glGenTextures(1, &shadowTex);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	auto loc = glGetUniformLocation(shadowPass2Shader->getShaderID(), "shadowTex");
	// First, activate texture unit (relative to GL_TEXTURE0)
	glActiveTexture(GL_TEXTURE0 + 1);
	// Second, tell "texture" sampler to use the 1st texture unit:
	glUniform1i(loc, 1);

	return true;
}

void Scene4::HandleEvents(const SDL_Event &ev) {}

void Scene4::Update(float deltatime) {
	tempdeltatime += deltatime;
	//std::cout << tempdeltatime << "\n";
}

void Scene4::Render() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawBuffer(GL_NONE); //Disable drawing colors
	glReadBuffer(GL_NONE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Camera LookAtM from light's position
	lightViewM = glm::lookAt(glm::vec3{ 2.0f, 2.0f, 2.0f }, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
	lightProjM = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTex, 0);
	
	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "FRAMEBUFFER ERROR: " << status << "/n";

	RenderPassOne();

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_FRONT); //Enable drawing colors
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	RenderPassTwo();
}

void Scene4::RenderPassOne()
{
	shadowPass1Shader->useProgram();

	//monkey->setModelMatrix(glm::rotate(glm::mat4{ 1.0f }, tempdeltatime, glm::vec3{ 0.0f, 1.0f, 0.0f }));
	shadowMVP1 = lightProjM * lightViewM * monkey->getModelMatrix();
	auto loc = glGetUniformLocation(shadowPass1Shader->getShaderID(), "shadowMVP");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(shadowMVP1));

	monkey->Render();

	shadowMVP1 = lightProjM * lightViewM * plane->getModelMatrix();
	loc = glGetUniformLocation(shadowPass1Shader->getShaderID(), "shadowMVP");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(shadowMVP1));

	plane->Render();
}

void Scene4::RenderPassTwo()
{
	monkey->getShader()->useProgram();

	shadowMVP2 = biasMatrix * lightProjM * lightViewM * monkey->getModelMatrix();
	monkey->sendMat4ToShader("shadowMVP2", shadowMVP2);
	
	//Construct MV matrix and pass it to shader
	auto mv = camera->getViewMatrix() * monkey->getModelMatrix();
	monkey->sendMat4ToShader("mvM", mv);

	//Construct normal matrix and pass it to shader
	auto normM = glm::transpose(glm::inverse(mv));
	monkey->sendMat4ToShader("normM", normM);

	monkey->Render();

	//PLANE////////////////////////////////////////////////////////////////////
	plane->getShader()->useProgram();

	shadowMVP2 = biasMatrix * lightProjM * lightViewM * plane->getModelMatrix();
	plane->sendMat4ToShader("shadowMVP2", shadowMVP2);

	//MV MATRIX
	mv = camera->getViewMatrix() * plane->getModelMatrix();
	plane->sendMat4ToShader("mvM", mv);

	//NORMAL MATRIX
	normM = glm::transpose(glm::inverse(mv));
	plane->sendMat4ToShader("normM", normM);

	plane->Render();

}
