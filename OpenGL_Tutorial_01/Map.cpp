#include "Map.h"
#include "Tile.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include "MapReader.h"
#include "ResourceLoader.h"

constexpr int TILE_OFFSET = 5;

Map::Map() {}
Map::~Map() {}

bool Map::Load(const std::string_view filepath, std::map<MESH, std::shared_ptr<Mesh>>& meshes, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& tex)
{
    auto mapString = MapReader::ReadMapFromFile(filepath);
    MAP_WIDTH = (int)sqrt(mapString.size());
    int tileID = 0;

    for (const auto& s : mapString) {

        switch (s) {
        case 'o': // o is a regular tile
        {
            auto tile = std::make_unique<Tile>();
            tile->Load(meshes[MESH::TILE_BASE], shader, tex);
            tile->setId(tileID); //tile ids are just numbers from 0 to n.
            tiles.push_back(std::move(tile));
            tileID++;
        }
            break;

        case 'O': // o is a regular tile AND passthrough
        {
            auto tile = std::make_unique<Tile>();
            tile->Load(meshes[MESH::TILE_BASE], shader, tex);
            tile->setId(tileID); //tile ids are just numbers from 0 to n.
            tile->setIsPassThrough(true);
            tiles.push_back(std::move(tile));
            tileID++;
        }
        break;

        case 'f': // f is goal
        {
            auto tile = std::make_unique<Tile>();
            tile->Load(meshes[MESH::TILE_GOAL], shader, tex);
            tile->setId(tileID); //tile ids are just numbers from 0 to n.
            tile->setIsLast(true);
            tiles.push_back(std::move(tile));
            tileID++;
        }
            break;

        case 's': // s is starting position
        {
            auto tile = std::make_unique<Tile>();
            tile->Load(meshes[MESH::TILE_START], shader, tex);
            tile->setId(tileID); //tile ids are just numbers from 0 to n.
            tile->setIsFirst(true);
            tiles.push_back(std::move(tile));
            tileID++;
        }
            break;

        case 'S': // s is starting position AND passthrough
        {
            auto tile = std::make_unique<Tile>();
            tile->Load(meshes[MESH::TILE_START], shader, tex);
            tile->setId(tileID); //tile ids are just numbers from 0 to n.
            tile->setIsFirst(true);
            tile->setIsPassThrough(true);
            tiles.push_back(std::move(tile));
            tileID++;
        }
        break;

        case 'b': // blocks the wayW
        {
            auto tile = std::make_unique<Tile>();
            tile->Load(meshes[MESH::TILE_BLOCK], shader, tex);
            tile->setId(tileID); //tile ids are just numbers from 0 to n.
            tile->setIsBlock(true);
            tile->setIsIntersectedOnce(true);
            tiles.push_back(std::move(tile));
            tileID++;
        }
            break;

        default:
            break;
        }
    }

    if (tiles.empty()) {
        std::cout << "ERROR: Map is empty!\n";
        return false;
    }

    for (const auto& tile : tiles) {
        tile->subscribe(collisionObserver);
    }

    return true;
}

void Map::Render() {
    for (auto& tile : tiles) {

        //Model Matrix for each tile
        tile->getTileObject()->getShader()->useProgram();
        tile->getTileObject()->getShader()->sendMatrixToShader("modelM", tile->getTileObject()->getModelMatrix());
        //Normal matrix for each tile
        auto normM = glm::transpose(glm::inverse(tile->getTileObject()->getModelMatrix()));
        tile->getTileObject()->getShader()->sendMatrixToShader("normalM", normM);

        tile->Render();
    }
}

void Map::setTileModelM() const
{
    for (auto& tile : tiles) {
        tile->getTileObject()->setModelMatrix(glm::translate(glm::mat4{ 1.0f }, tile->getPosition()));
    }
}

void Map::generateTilePositions()
{
    auto pos = glm::vec3{ 0.0f };

    for (int z = -MAP_WIDTH; z < 0; z++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            pos.x = x * TILE_OFFSET;
            pos.z = z * TILE_OFFSET + TILE_OFFSET;
            positions.push_back(pos);
        }
    }
}

void Map::setTilePositions()
{
    //Using positions iterator to set individual tile positions
    auto positionsIterator = positions.begin();

    for (auto& tile : tiles) {
        
        tile->setPosition(*positionsIterator);

        if (positionsIterator != positions.end())
            positionsIterator = std::next(positionsIterator);
    }
}


glm::vec3 Map::getStartingPosition()
{
    glm::vec3 startingPosition;

    for (const auto& t : tiles) {
        if (t->getIsFirst() == true) {
            startingPosition = t->getPosition();
            break;
        }
    }
    return startingPosition;
}

bool Map::checkMapForWin() const
{
    return (*GetCurrentTileIndex())->getIsLast() == true ? true : false;
}

bool Map::checkIfAllTilesTraversed() const
{
    return std::all_of(tiles.begin(), tiles.end(), [](const std::unique_ptr<Tile>& tile)
        {
            return tile->getIsIntersectedOnce() == true;
        });
}

bool Map::checkMapForLose() const
{
    bool isInterceptingLastTile = false;
    auto currentTileIndex = GetCurrentTileIndex();

    if (currentTileIndex != tiles.end()) {
        isInterceptingLastTile = (*currentTileIndex)->getIsLast() == true;
    }

    bool hasInterceptedATileTwice = std::any_of(tiles.begin(), tiles.end(), [](const std::unique_ptr<Tile>& tile) {
        //If counter is greater than 1 then the player has intersected the same tile twice
        return tile->getIntersectCounter() > 1;
        });

    return isInterceptingLastTile || hasInterceptedATileTwice;
}

std::vector<std::unique_ptr<class Tile>>::const_iterator Map::GetCurrentTileIndex() const
{
    return std::find_if(tiles.begin(), tiles.end(), [](const std::unique_ptr<Tile>& tile)
        {
            return tile->getIsIntersecting() == true;
        });
}
