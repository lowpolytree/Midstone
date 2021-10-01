#pragma once
#include "AABB.h"
#include "glm/vec3.hpp"
#include "Ray.h"

class Collisions
{
public:
	static bool Intersection(const AABB& a, const glm::vec3& aOffset, const AABB& b, const glm::vec3& bOffset);
	static bool Intersection(const Ray& r, const AABB& b, const glm::vec3& bOffset);
};

