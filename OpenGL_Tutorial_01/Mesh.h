#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class Mesh
{
public:
	Mesh(std::vector<glm::vec3>& position_,
		 std::vector<glm::vec2>& uvCoord_,
		 std::vector<glm::vec3>& normals_);
	~Mesh();

	void Create();
	void Render();
	void CleanUp();

	auto& getVertices() const { return position; }

private:
	unsigned int vbo, vao;
	std::vector<glm::vec3> position;
	std::vector<glm::vec2> uvCoord;
	std::vector<glm::vec3> normals;
};