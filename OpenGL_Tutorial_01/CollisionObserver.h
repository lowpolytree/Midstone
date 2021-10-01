#pragma once
#include "Observer.h"
class Tile;

class CollisionObserver : public Observer<Tile>
{
public:
	void propertyChanged(Tile& source, const std::string& propertyName) override;
};