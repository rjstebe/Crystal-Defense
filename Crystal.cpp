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
	setAltitude(1);
	// Set up crystal health UI element
	df::ViewObject* crystal_health = new df::ViewObject();
	crystal_health->setColor(df::CYAN);
	crystal_health->setLocation(df::TOP_LEFT);
	crystal_health->setViewString("crystal");
	crystal_health->setValue(CRYSTAL_HEALTH);
}

Crystal::~Crystal()
{

}

// Returns 1 if event was handled, else 0;
int Crystal::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == DAMAGE_EVENT) {
		const EventDamage* p_ed = dynamic_cast<const EventDamage*>(p_e);
		damaged(p_ed);
	}
	return 0;
}

// When damaged, update health and corresponding UI elements.
void Crystal::damaged(const EventDamage* p_ed) {
	LM.writeLog(-5, "Crystal::eventHandler(): received damage event");
	health -= p_ed->getDamage();
	// Send view event to view.
	df::EventView ev("crystal", -p_ed->getDamage(), true);
	WM.onEvent(&ev);
}
