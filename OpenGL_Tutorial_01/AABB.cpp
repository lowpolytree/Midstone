#include "AABB.h"
#include "Mesh.h"
#include "Shader.h"
#include "ResourceLoader.h"
#include <iostream>
#include <vector>
#include <limits>
#include <glm/gtc/matrix_transform.hpp>

AABB::AABB() {}

AABB::~AABB() {
	glDeleteBuffers(1, &bbVBO);
	glDeleteBuffers(1, &bbEBO);
	glDeleteVertexArrays(1, &bbVAO);
}

bool AABB::Construct(const std::shared_ptr<class Mesh>& mesh)
{
	if (mesh->getVertices().size() == 0) {
		std::cout << "ERROR: Bounding box not contructed. Vertex array size is zero.\n";
		return false;
	}

	//BUFFERS AND DATA
	std::vector<GLfloat> bbVertices 
	{
		-0.5, -0.5,  0.5, //1
		 0.5, -0.5,  0.5, //2
		 0.5,  0.5,  0.5, //3
		-0.5,  0.5,  0.5, //4
		-0.5,  0.5, -0.5, //5
		 0.5,  0.5, -0.5, //6
		 0.5, -0.5, -0.5, //7
		-0.5, -0.5, -0.5  //8
	};

	std::vector<GLuint> indices
	{
		0, 1, 2, 3,               //Front line loop
		4, 5, 6, 7,               //Back line loop
		1, 6, 2, 5, 0, 7, 3, 4    //Connecting edges
	};

	glGenVertexArrays(1, &bbVAO);
	glGenBuffers(1, &bbVBO);
	glGenBuffers(1, &bbEBO);

	glBindVertexArray(bbVAO);             // <<-VAO BOUND
	glBindBuffer(GL_ARRAY_BUFFER, bbVBO); // <<-VBO BOUND
	glBufferData(GL_ARRAY_BUFFER, bbVertices.size() * sizeof(GLfloat), &bbVertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bbEBO);  // <<-EBO BOUND
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);                     // <<-VAO UNBOUND
	glBindBuffer(GL_ARRAY_BUFFER, 0);         // <<-VBO UNBOUND
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // <<-EBO UNBOUND

	//CALCULATING MIN MAX EXTENTS
	min.x = min.y = min.z = std::numeric_limits<float>::max();
	max.x = max.y = max.z = std::numeric_limits<float>::min();

	for (const auto& vert : mesh->getVertices()) {
		if (vert.x < min.x) min.x = vert.x;
		if (vert.x > max.x) max.x = vert.x;
		if (vert.y < min.y) min.y = vert.y;
		if (vert.y > max.y) max.y = vert.y;
		if (vert.z < min.z) min.z = vert.z;
		if (vert.z > max.z) max.z = vert.z;
	}

	//TRANSFORMATIONS
	auto size = glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
	auto center = glm::vec3((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, (min.z + max.z) * 0.5f);
	modelM = glm::translate(glm::mat4{ 1.0f }, center) * glm::scale(glm::mat4{ 1.0f }, size);

	return true;
}

bool AABB::Intersect(const AABB& other)
{
	if (min.x >= other.max.x) return false;
	if (max.x <= other.min.x) return false;
	if (min.y >= other.max.y) return false;
	if (max.y <= other.min.y) return false;
	if (min.z >= other.max.z) return false;
	if (max.z <= other.min.z) return false;
	return true;
}

void AABB::Render()
{
	ResourceLoader::shaders[SHADER::AABB]->useProgram();

	auto newModel = parentM * modelM;
	ResourceLoader::shaders[SHADER::AABB]->sendMatrixToShader("modelM", newModel);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(bbVAO);

	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(4 * sizeof(GLuint)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (void*)(8 * sizeof(GLuint)));

	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
