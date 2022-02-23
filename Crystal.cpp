#include "Crystal.h"

// Engine includes.
#include "LogManager.h"
#include "ViewObject.h"
#include "EventView.h"
#include "WorldManager.h"

// Game includes.
#include "EventDamage.h"

Crystal::Crystal()
{
	setType("Crystal");
	setSprite("crystal");
	df::Vector p(40, 10);
	setPosition(p);
}

Crystal::~Crystal()
{

}

// Returns 1 if event was handled, else 0;
int Crystal::eventHandler(const df::Event* p_e)
{
	LM.writeLog(-5, "Crystal::eventHandler(): event type: %s", p_e->getType().c_str());
	if (p_e->getType() == DAMAGE_EVENT) {
		const EventDamage* p_ed = dynamic_cast<const EventDamage*>(p_e);
		LM.writeLog(-5, "Crystal::eventHandler(): received damage event");
		health -= p_ed->getDamage();
		// send view event to view
		df::EventView ev("crystal health", -p_ed->getDamage(), true);
		WM.onEvent(&ev);
	}
	return 0;
}

void Crystal::hit(const df::EventCollision* p_collision_event)
{

}
