#include "PowerUp.h"

// Engine includes.
#include "EventCollision.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

int PowerUp::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_ec = dynamic_cast<const df::EventCollision*>(p_e);
		hit(p_ec);
	}
	return 0;
}

void PowerUp::hit(const df::EventCollision* p_collision_event)
{
}