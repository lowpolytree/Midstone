#include "Cube.h"
#include <iostream>
#include "glew.h"
#include "SDL.h"
#include "SDL_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

Cube::Cube(): shader(nullptr), mesh(nullptr), tex(nullptr) {}

Cube::Cube(Shader *shader_): shader(shader_), mesh(nullptr), tex(nullptr) {
	Create();
}

Cube::~Cube() {
	if (tex) delete tex, tex = nullptr;
	if (mesh) delete mesh, mesh = nullptr;
	if (shader) delete shader, shader = nullptr;
}

bool Cube::Create() {

	std::vector<glm::vec3> positions = {
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3( 0.5f, -0.5f, -0.5f),
		glm::vec3( 0.5f,  0.5f, -0.5f),
		glm::vec3( 0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3( 0.5f, -0.5f,  0.5f),
		glm::vec3( 0.5f,  0.5f,  0.5f),
		glm::vec3( 0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
		glm::vec3( 0.5f,  0.5f,  0.5f),
		glm::vec3( 0.5f,  0.5f, -0.5f),
		glm::vec3( 0.5f, -0.5f, -0.5f),
		glm::vec3( 0.5f, -0.5f, -0.5f),
		glm::vec3( 0.5f, -0.5f,  0.5f),
		glm::vec3( 0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3( 0.5f, -0.5f, -0.5f),
		glm::vec3( 0.5f, -0.5f,  0.5f),
		glm::vec3( 0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f),
		glm::vec3( 0.5f,  0.5f, -0.5f),
		glm::vec3( 0.5f,  0.5f,  0.5f),
		glm::vec3( 0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f, -0.5f)
	};
	std::vector<glm::vec2> uv = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f)
	};

	mesh = new Mesh(positions, uv);

	if (!mesh)
		std::cout << "Error: Failed to load mesh!\n";

	//TEXTURE//////////////////////////////////////////////////////////////////////
	tex = new Texture();

	if (!tex->loadTexture("Resources\\Art\\tex_stone_handpainted.png"))
		std::cout << "Error: Failed to load texture!\n";

	///UNIFORMS////////////////////////////////////////////////////////////////

	//Transforms
	//glm::mat4 modelM = glm::mat4(1.0f);
	modelM = glm::rotate(modelM, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//glm::mat4 viewM = glm::mat4(1.0f);
	//translating the whole scene along Z by -3.0f
	viewM = glm::translate(viewM, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projectionM;
	projectionM = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	shader->useProgram();
	//Projection matrix rarely changes it's best to set it only once
	int projLoc = glGetUniformLocation(shader->getShaderID(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionM));

	return true;
}
void Cube::HandleEvents(const SDL_Event &ev) {}

void Cube::Update(float deltatime) {
	//Rotating the cuber around Y and X
	modelM = glm::rotate(modelM, 0.005f, glm::vec3(0.0f, 1.0f, 0.0f));
	modelM = glm::rotate(modelM, 0.002f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Cube::Render() {

	shader->useProgram();
	//UNIFORMS////////////////////////////////////////
	int modelLoc = glGetUniformLocation(shader->getShaderID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));

	int viewLoc = glGetUniformLocation(shader->getShaderID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewM));

	//DRAW/////////////////////////////////////////////
	glActiveTexture(GL_TEXTURE0);
	if(tex)
		glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glUniform1i(glGetUniformLocation(shader->getShaderID(), "tex01"), 0);
	mesh->Render();
	glBindTexture(GL_TEXTURE_2D, 0);
}