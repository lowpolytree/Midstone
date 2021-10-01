#pragma once
#include <memory>
#include "glm/vec3.hpp"
#include "Observable.h"
#include "CollisionObserver.h"

class Tile : public Observable<Tile>
{
public:
	Tile();
	~Tile();

	bool Load(const std::shared_ptr<class Mesh>& mesh, const std::shared_ptr<class Shader>& shader, const std::shared_ptr<class Texture>& tex);
	void Render();

	auto& getTileObject() const { return tile; }
	void setPosition(const glm::vec3& pos_) { pos = pos_; }
	auto& getPosition() const { return pos; }

	auto getId() const { return id; }
	void setId(const int id_) { id = id_; }

	auto getIsIntersecting() const { return isIntersecting; }
	void setIsIntersecting(const bool val) { 
		if (isIntersecting == val) return;
		isIntersecting = val;
		if (val)
			notify(*this, "onCollisionEnter");
		if (!val)
			notify(*this, "onCollisionExit");
	}

	auto getIsIntersectedOnce() const { return isIntersectedOnce; }
	void setIsIntersectedOnce(const bool val) { isIntersectedOnce = val; }

	int getIntersectCounter() const { return intersectCounter; }
	void setIntersectCounter(const int val) { intersectCounter = val; }

	auto& getAABB() const { return aabb; }

	bool getIsFirst() const { return isFirst; }
	bool getIsLast() const { return isLast; }
	void setIsFirst(bool status) { isFirst = status; }
	void setIsLast(bool status) { isLast = status; }

private:
	std::unique_ptr<class DemoObject> tile;
	glm::vec3 pos;
	std::unique_ptr<class AABB> aabb;
	int id;
	int intersectCounter;
	bool isIntersecting;
	bool isIntersectedOnce;
	bool isFirst;
	bool isLast;
};

