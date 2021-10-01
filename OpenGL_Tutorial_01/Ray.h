#pragma once
#include "glm/vec3.hpp"

class Ray
{
public:
	Ray();
	Ray(const glm::vec3& origin, const glm::vec3& dir);
	~Ray();

	glm::vec3 currentPosition(const float t) const;

public:
	glm::vec3 origin;
	glm::vec3 dir;
	glm::vec3 invdir;
	int sign[3];
};
