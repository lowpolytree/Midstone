#pragma once

#include <vector>
#include "glm//vec2.hpp"
#include "glm//vec3.hpp"

class OBJLoader {
public:

	OBJLoader(const OBJLoader&) = delete;  /// Copy constructor
	OBJLoader(OBJLoader&&) = delete;       /// Move constructor
	OBJLoader& operator=(const OBJLoader&) = delete; /// Copy operator
	OBJLoader& operator=(OBJLoader&&) = delete;      /// Move operator

	static std::vector<glm::vec3> vertices;
	static std::vector<glm::vec2> uvs;
	static std::vector<glm::vec3> normals;

	static bool loadOBJ(const char* path);
};