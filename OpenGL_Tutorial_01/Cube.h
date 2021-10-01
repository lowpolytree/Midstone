#pragma once
#include "GameObject.h"
#include "glm/matrix.hpp"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

class Cube: public GameObject
{
public:
	Cube();
	Cube(Shader *shader_);
	~Cube();

	bool Create();
	void HandleEvents(const SDL_Event &ev);
	void Update(float deltatime);
	void Render();

private:
	Shader *shader;
	Mesh *mesh;
	Texture *tex;
	glm::mat4 modelM{ 1.0f };
	glm::mat4 viewM{ 1.0f };
	unsigned int texID;
};
