#include "ResourceLoader.h"
#include <utility>
#include "OBJLoader.h"

std::map<MESH, std::shared_ptr<Mesh>>    ResourceLoader::meshes;
std::map<TEXTURE, std::shared_ptr<Texture>> ResourceLoader::textures;
std::map<SHADER, std::shared_ptr<Shader>>  ResourceLoader::shaders;

bool ResourceLoader::LoadResources()
{
	//LOADING MESHES
	//PLAYER
	if (!OBJLoader::loadOBJ("Resources\\Models\\Player.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::PLAYER, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	//TILES
	if (!OBJLoader::loadOBJ("Resources\\Models\\Tile_Base.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::TILE_BASE, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Tile_Start.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::TILE_START, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Tile_Goal.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::TILE_GOAL, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Tile_Block.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::TILE_BLOCK, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Tile_Passthrough.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::TILE_PASSTHROUGH, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Tile_Start_Passthrough.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::TILE_START_PASSTHROUGH, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	//ENVIRONMENT
	if (!OBJLoader::loadOBJ("Resources\\Models\\Ground1.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::GROUND1, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Ground2.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::GROUND2, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Ground3.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::GROUND3, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	if (!OBJLoader::loadOBJ("Resources\\Models\\Flame.obj"))
		return false;

	meshes.insert(std::make_pair(MESH::FLAME, std::make_shared<Mesh>(OBJLoader::vertices, OBJLoader::uvs, OBJLoader::normals)));

	//LOADING TEXTURES
	textures.insert(std::make_pair(TEXTURE::PALETTE, std::make_shared<Texture>()));
	textures[TEXTURE::PALETTE]->loadTexture("Resources\\Art\\t_colors.png");
	textures.insert(std::make_pair(TEXTURE::UI_BUTTON, std::make_shared<Texture>()));
	textures[TEXTURE::UI_BUTTON]->loadTexture("Resources\\Art\\ui_button_01.png");
	textures.insert(std::make_pair(TEXTURE::UI_BACKGROUND, std::make_shared<Texture>()));
	textures[TEXTURE::UI_BACKGROUND]->loadTexture("Resources\\Art\\ui_background.png");
	textures.insert(std::make_pair(TEXTURE::UI_GAMEOVER, std::make_shared<Texture>()));
	textures[TEXTURE::UI_GAMEOVER]->loadTexture("Resources\\Art\\ui_gameover.png");
	textures.insert(std::make_pair(TEXTURE::UI_WIN, std::make_shared<Texture>()));
	textures[TEXTURE::UI_WIN]->loadTexture("Resources\\Art\\ui_winscreen.png");

	//LOADING SHADERS
	shaders.insert(std::make_pair(SHADER::LAMBERT, std::make_shared<Shader>("Resources\\Shaders\\LambertShader.vert", "Resources\\Shaders\\LambertShader.frag")));
	shaders.insert(std::make_pair(SHADER::AABB, std::make_shared<Shader>("Resources\\Shaders\\BoundingBox.vert", "Resources\\Shaders\\BoundingBox.frag")));
	shaders.insert(std::make_pair(SHADER::TEXT, std::make_shared<Shader>("Resources\\Shaders\\TextShader.vert", "Resources\\Shaders\\TextShader.frag")));
	shaders.insert(std::make_pair(SHADER::UI, std::make_shared<Shader>("Resources\\Shaders\\UIShader.vert", "Resources\\Shaders\\UIShader.frag")));
	shaders.insert(std::make_pair(SHADER::UI_IMAGE, std::make_shared<Shader>("Resources\\Shaders\\UIImage.vert", "Resources\\Shaders\\UIImage.frag")));
	shaders.insert(std::make_pair(SHADER::TILE, std::make_shared<Shader>("Resources\\Shaders\\TileShader.vert", "Resources\\Shaders\\TileShader.frag")));
	shaders.insert(std::make_pair(SHADER::FIRE, std::make_shared<Shader>("Resources\\Shaders\\FireShader.vert", "Resources\\Shaders\\FireShader.frag")));

	return true;
}
