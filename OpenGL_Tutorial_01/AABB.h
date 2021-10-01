#pragma once
#include "glew.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include <memory>

class AABB
{
public:
	AABB();
	~AABB();

	bool Construct(const std::shared_ptr<class Mesh>& mesh);
	bool Intersect(const AABB& other);
	void Render();

	auto& getModelMatrix() const { return modelM; }
	void setModelMatrix(const glm::mat4& mm) { modelM = mm; }
	void setParentModelMatrix(const glm::mat4& pm) { parentM = pm; }

	auto Min() const { return min; }
	auto Max() const { return max; }

private:
	GLuint bbVBO, bbVAO, bbEBO;
	glm::vec3 min;
	glm::vec3 max;
	
	glm::mat4 modelM;
	glm::mat4 parentM;
};

