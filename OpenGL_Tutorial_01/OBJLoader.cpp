#include "OBJLoader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>

std::vector<glm::vec3> OBJLoader::vertices;
std::vector<glm::vec2> OBJLoader::uvs;
std::vector<glm::vec3> OBJLoader::normals;

bool OBJLoader::loadOBJ(const char* path)
{
	if (!vertices.empty())  vertices.clear();
	if (!uvs.empty())       uvs.clear();
	if (!normals.empty())   normals.clear();

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path)) {
		std::cout << "ERROR: OBJLoader failed to load! a model!\n";
		return false;
	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			glm::vec3 vertex{};
			glm::vec2 uv{};
			glm::vec3 normal{};

			vertex = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			uv = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			normal = {
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2]
			};

			vertices.push_back(vertex);
			uvs.push_back(uv);
			normals.push_back(normal);
		}
	}
	return true;
}
