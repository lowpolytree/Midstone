#include "DemoObject.h"

DemoObject::DemoObject() {}

DemoObject::DemoObject(const std::shared_ptr<Mesh>& mesh_,
					   const std::shared_ptr<Shader>& shader_,
					   const std::shared_ptr<Texture>& tex_): mesh(mesh_), shader(shader_), tex(tex_) {}

DemoObject::~DemoObject() {}

bool DemoObject::Create() { return true; }

void DemoObject::HandleEvents(const SDL_Event& ev) {}

void DemoObject::Update(float deltatime) {}

void DemoObject::Render() {

	shader->useProgram();

	if (tex) {
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	}

	shader->sendMatrixToShader("modelM", modelM);
	shader->sendMatrixToShader("normalM", normalM);

	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void DemoObject::sendMat4ToShader(const std::string& name, const glm::mat4& m)
{
	shader->useProgram();
	const auto loc = glGetUniformLocation(shader->getShaderID(), name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void DemoObject::sendVec3ToShader(const std::string& name, const glm::vec3& v)
{
	shader->useProgram();
	const auto loc = glGetUniformLocation(shader->getShaderID(), name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(v));
}

void DemoObject::sendFloatToShader(const std::string& name, const float v)
{
	shader->useProgram();
	const auto loc = glGetUniformLocation(shader->getShaderID(), name.c_str());
	glUniform1f(loc, v);
}
