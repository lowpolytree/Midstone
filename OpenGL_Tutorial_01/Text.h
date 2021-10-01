#pragma once
#include <string>
#include "glm/matrix.hpp"
#include "glm/vec3.hpp"

struct PositionText {
	float x;
	float y;
};

class Text
{
public:
	Text();
	~Text();

	bool Load(const std::string& filepath, int textSize, const std::string& textMessage, class SDL_Color color);
	void Render();

	void UpdateModel(const PositionText pos, const float scale, const glm::mat4& parent);

private:
	unsigned int texID;
	unsigned int VAO, VBO, EBO;
	glm::mat4 model;
	glm::mat4 projection;

};

