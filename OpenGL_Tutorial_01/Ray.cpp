#include "Ray.h"

Ray::Ray():origin(0.0f), dir(0.0f) {}

Ray::Ray(const glm::vec3& start, const glm::vec3& dir): origin(start), dir(dir){
	invdir.x = 1 / dir.x;
	invdir.y = 1 / dir.y;
	invdir.z = 1 / dir.z;

	sign[0] = (invdir.x < 0);
	sign[1] = (invdir.y < 0);
	sign[2] = (invdir.z < 0);
}

Ray::~Ray(){}

glm::vec3 Ray::currentPosition(const float t) const{
	//Calculate the position at t
	return origin + dir * t;
}