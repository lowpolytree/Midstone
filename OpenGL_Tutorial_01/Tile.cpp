#include "Tile.h"
#include "DemoObject.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "AABB.h"

Tile::Tile(){
	isIntersecting = false;
	isIntersectedOnce = false;
	isFirst = false;
	isLast = false;
	isBlock = false;
	isPassThrough = false;
}

Tile::~Tile(){}

bool Tile::Load(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& tex)
{
	tile = std::make_unique<DemoObject>(mesh, shader, tex);

	if (!tile) {
		std::cout << "ERROR: Tile failed to load!\n";
		return false;
	}

	aabb = std::make_unique<AABB>();
	if (!aabb->Construct(tile->getMesh())) {
		std::cout << "ERROR: Player AABB failed to construct!\n";
		return false;
	}

	return true;
}

void Tile::Render() {

	//Think about sending a batch of bools instead of one by one
	tile->getShader()->sendBoolToShader("isIntersectedOnce", isIntersectedOnce);
	tile->getShader()->sendBoolToShader("isLast", isLast);
	tile->Render();

	aabb->setParentModelMatrix(tile->getModelMatrix());
	aabb->Render();
}
