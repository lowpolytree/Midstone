#include "CollisionObserver.h"
#include <iostream>
#include "Tile.h"

void CollisionObserver::propertyChanged(Tile& source, const std::string& propertyName)
{
	if (propertyName == "onCollisionEnter") {
		std::cout << "On Collision Enter!\n";
		source.setIsIntersectedOnce(true);
		//Setting a tile's intersection counter to +1 
		auto counter = source.getIntersectCounter();
		source.setIntersectCounter(++counter);
	}

	if (propertyName == "onCollisionExit") {
		std::cout << "On Collision Exit!\n";
	}
}
