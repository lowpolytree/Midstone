#include "Collisions.h"
//delete
#include <iostream>

constexpr int MIN_BOUNDARY = 0;
constexpr int MAX_BOUNDARY = 8;

bool Collisions::Intersection(const AABB& a, const glm::vec3& aOffset, const AABB& b, const glm::vec3& bOffset)
{
	auto aMin = a.Min() + aOffset;
	auto aMax = a.Max() + aOffset;
	auto bMin = b.Min() + bOffset;
	auto bMax = b.Max() + bOffset;

	if (aMin.x >= bMax.x) return false;
	if (aMax.x <= bMin.x) return false;
	if (aMin.y >= bMax.y) return false;
	if (aMax.y <= bMin.y) return false;
	if (aMin.z >= bMax.z) return false;
	if (aMax.z <= bMin.z) return false;

	return true;
}

bool Collisions::Intersection(const Ray& r, const AABB& b, const glm::vec3& bOffset)
{
    auto min = b.Min() + bOffset;
    auto max = b.Max() + bOffset;

    float tmin = (min.x - r.origin.x) / r.dir.x;
    float tmax = (max.x - r.origin.x) / r.dir.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tzmin = (min.z - r.origin.z) / r.dir.z;
    float tzmax = (max.z - r.origin.z) / r.dir.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    if (tmin < MIN_BOUNDARY || tmax > MAX_BOUNDARY) // To avoid selecting unecessary tiles
        return false;

    return true;
}
