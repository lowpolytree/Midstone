#include "Mesh.h"
#include <glew.h>

Mesh::Mesh(std::vector<glm::vec3>& position_,
		   std::vector<glm::vec2>& uvCoord_,
		   std::vector<glm::vec3>& normals_){
	position = position_;
	uvCoord = uvCoord_;
	normals = normals_;
	Create();
}

Mesh::~Mesh(){
	CleanUp();
}

void Mesh::Create() {

	//GENERATING VERTEX ARRAY and BUFFER OBJECTS
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	//BIND VAO and VBO
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(glm::vec3)
								+ uvCoord.size() * sizeof(glm::vec2)
								+ normals.size() * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, position.size() * sizeof(glm::vec3), &position[0]);
	glBufferSubData(GL_ARRAY_BUFFER, position.size() * sizeof(glm::vec3), uvCoord.size() * sizeof(glm::vec2), &uvCoord[0]);
	glBufferSubData(GL_ARRAY_BUFFER, position.size() * sizeof(glm::vec3) + uvCoord.size() * sizeof(glm::vec2), normals.size() * sizeof(glm::vec3), &normals[0]);

	//VERTEX ATTRIBUTES//////////////////////////
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(position.size() * sizeof(glm::vec3)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(position.size() * sizeof(glm::vec3) + uvCoord.size() * sizeof(glm::vec2)));
}

void Mesh::Render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, position.size());
	glBindVertexArray(0);
}

void Mesh::CleanUp(){
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
