#include "ResourceLoader.h"
#include <utility>
#include "OBJLoader.h"

std::map<MESH, std::shared_ptr<Mesh>>    ResourceLoader::meshes;
std::map<TEXTURE, std::shared_ptr<Texture>> ResourceLoader::textures;
std::map<SHADER, std::shared_ptr<Shader>>  ResourceLoader::shaders;

bool ResourceLoader::LoadResources()
{
	//LOADING MESHES
	//TILE MESH
	if (!OBJLoader::loadOBJ("Resources\\Models\\Tile.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::TILE, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	//PLAYER MESH
	if (!OBJLoader::loadOBJ("Resources\\Models\\Player.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::PLAYER, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	//GROUND MESH
	if (!OBJLoader::loadOBJ("Resources\\Models\\Ground.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::GROUND, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	//LOADING TEXTURES
	textures.insert(std::make_pair(TEXTURE::PALETTE, std::make_shared<Texture>()));
	textures[TEXTURE::PALETTE]->loadTexture("Resources\\Art\\colors.png");
	textures.insert(std::make_pair(TEXTURE::UI_BUTTON, std::make_shared<Texture>()));
	textures[TEXTURE::UI_BUTTON]->loadTexture("Resources\\Art\\ui_button_01.png");

	//LOADING SHADERS
	shaders.insert(std::make_pair(SHADER::LAMBERT, std::make_shared<Shader>("Resources\\Shaders\\LambertShader.vert", "Resources\\Shaders\\LambertShader.frag")));
	shaders.insert(std::make_pair(SHADER::AABB, std::make_shared<Shader>("Resources\\Shaders\\BoundingBox.vert", "Resources\\Shaders\\BoundingBox.frag")));
	shaders.insert(std::make_pair(SHADER::TEXT, std::make_shared<Shader>("Resources\\Shaders\\TextShader.vert", "Resources\\Shaders\\TextShader.frag")));
	shaders.insert(std::make_pair(SHADER::UI, std::make_shared<Shader>("Resources\\Shaders\\UIShader.vert", "Resources\\Shaders\\UIShader.frag")));
	shaders.insert(std::make_pair(SHADER::TILE, std::make_shared<Shader>("Resources\\Shaders\\TileShader.vert", "Resources\\Shaders\\TileShader.frag")));

	return true;
}
