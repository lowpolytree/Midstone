#pragma once
#include <map>
#include <string>
#include <memory>
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

enum class MESH {
	TILE_BASE,
	TILE_START,
	TILE_GOAL,
	TILE_BLOCK,
	PLAYER,
	GROUND,
	GRASS
};

enum class TEXTURE {
	PALETTE,
	UI_BUTTON,
};

enum class SHADER {
	LAMBERT,
	AABB,
	TEXT,
	UI,
	TILE,
};

class ResourceLoader
{
public:
	static bool LoadResources();

	static std::map<MESH, std::shared_ptr<Mesh>> meshes;
	static std::map<TEXTURE, std::shared_ptr<Texture>> textures;
	static std::map<SHADER, std::shared_ptr<Shader>> shaders;

private:
};

