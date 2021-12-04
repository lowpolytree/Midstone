#pragma once
#include "glm/matrix.hpp"
#include <memory>

class Image
{
public:
	Image(const float x, const float y, const float w, const float h, std::shared_ptr<class Texture> tex);

	void OnCreate();
	void Render();

private:
	float width, height, posx, posy;
	
	unsigned int VAO, VBO, EBO;

	glm::mat4 model;
	glm::mat4 projection;
	std::shared_ptr<class Texture> texture;
};

