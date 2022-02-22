#include "Crystal.h"

Crystal::Crystal()
{
	setType("Crystal");
	setSprite("crystal");
	df::Vector p(5, 10);
	setPosition(p);
}

Crystal::~Crystal()
{
}

int Crystal::eventHandler(const df::Event* p_e)
{
	return 0;
}

void Crystal::hit(const df::EventCollision* p_collision_event)
{
}
