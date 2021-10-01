#pragma once
#include "GameObject.h"
#include <memory>
#include <string>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include <glm/vec3.hpp>
#include "glm//matrix.hpp"
#include <glm/gtc/type_ptr.hpp>

class DemoObject : public GameObject
{
public:
	DemoObject();
	DemoObject(const std::shared_ptr<Mesh> &mesh_, const std::shared_ptr<Shader> &shader_, const std::shared_ptr<Texture> &tex_);
	~DemoObject();

	bool Create();
	void HandleEvents(const SDL_Event& ev);
	void Update(float deltatime);
	void Render();

	auto& getShader() const { return shader; }
	auto& getMesh() const { return mesh; }

	auto& getModelMatrix() const { return modelM; }
	void setModelMatrix(const glm::mat4& mm) { modelM = mm; }

	auto& getNormalMatrix() const { return normalM; }
	void setNormalMatrix(const glm::mat4& nm) { normalM = nm; }

	void sendMat4ToShader(const std::string& name, const glm::mat4& m);
	void sendVec3ToShader(const std::string& name, const glm::vec3& v);

private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Texture> tex;

	glm::mat4 modelM;
	glm::mat4 normalM;
};
