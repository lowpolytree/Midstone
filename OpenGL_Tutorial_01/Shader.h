#pragma once

#include "glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/vec4.hpp>
#include "glm//matrix.hpp"

class Shader
{
public:
	Shader();
	~Shader();
	Shader(const char* vertexPath_, const char* fragmentPath_);

	void useProgram();
	void deleteProgram();
	
	void sendMatrixToShader(const std::string& name, const glm::mat4& m) const;
	void sendVector3ToShader(const std::string& name, const glm::vec3& v) const;
	void sendBoolToShader(const std::string& name, const bool v) const;

	unsigned int getShaderID() const { return m_Id; }

private:
	unsigned int m_Id;
};
