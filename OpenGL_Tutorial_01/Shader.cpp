#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(){}
Shader::~Shader(){}

Shader::Shader(const char* vertexPath_, const char* fragmentPath_){
	// Retrieve the vertex/fragment source code from filePath
	std::string vertCode, fragCode;
	std::ifstream vertFile, fragFile;

	vertFile.open(vertexPath_);
	fragFile.open(fragmentPath_);

	if (!vertFile.is_open() && !fragFile.is_open())
		std::cout << "ERROR::SHADER::FILE::FAILED::TO::OPEN!!\n";
	else {
		std::stringstream vertStream, fragStream;
		// read file's buffer contents into streams
		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();

		vertFile.close();
		fragFile.close();
		// convert stream into string
		vertCode = vertStream.str();
		fragCode = fragStream.str();
	}

	const char* vShaderCode = vertCode.c_str();
	const char* fShaderCode = fragCode.c_str();

	//CREATING SHADER PROGRAM
	unsigned int vertShader, fragShader;
	// VERTEX
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vShaderCode, NULL);
	glCompileShader(vertShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_Id = glCreateProgram();
	glAttachShader(m_Id, vertShader);
	glAttachShader(m_Id, fragShader);
	glLinkProgram(m_Id);

	glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
		std::cout << "ERROR::ANOTHER_SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

void Shader::useProgram(){
	glUseProgram(m_Id);
}

void Shader::deleteProgram() {
	glDeleteProgram(m_Id);
}

void Shader::sendMatrixToShader(const std::string& name, const glm::mat4& m) const
{
	glUseProgram(m_Id);
	glUniformMatrix4fv(glGetUniformLocation(m_Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::sendVector3ToShader(const std::string& name, const glm::vec3& v) const
{
	glUseProgram(m_Id);
	glUniform3fv(glGetUniformLocation(m_Id, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::sendBoolToShader(const std::string& name, const bool v) const
{
	glUseProgram(m_Id);
	glUniform1i(glGetUniformLocation(m_Id, name.c_str()), v);
}
