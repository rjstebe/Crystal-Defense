#include "Wall.h"

Wall::Wall()
{
	setType("Wall");
	setSprite("wall");
	df::Vector p(5, 5);
	setPosition(p);
}

Wall::~Wall()
{
}
