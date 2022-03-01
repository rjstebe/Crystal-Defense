#include "Crystal.h"

// Engine includes.
#include "LogManager.h"
#include "WorldManager.h"
#include "ViewObject.h"
#include "EventView.h"
#include "EventStep.h"

// Game includes.
#include "EventDamage.h"
#include "EventCrystalDeath.h"

Crystal::Crystal(df::Vector position)
{
	setType("Crystal");
	setSprite("crystal");
	setPosition(position);
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
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_es = dynamic_cast<const df::EventStep*>(p_e);
		step();
		return 1;
	}
	return 0;
}

// When damaged, update health and corresponding UI elements.
void Crystal::damaged(const EventDamage* p_ed) {
	LM.writeLog(-5, "Crystal::damaged(): received damage event");
	health -= p_ed->getDamage();
	// Send view event to view.
	df::EventView ev("crystal", -p_ed->getDamage(), true);
	WM.onEvent(&ev);
	if (health <= 0) {
		LM.writeLog(0, "Crystal::damaged(): Crystal died");
		EventCrystalDeath deth;
		WM.onEvent(&deth);
	}
}

// Each step, update regen cooldown, and if time, regen and update UI element.
void Crystal::step() {
	regen_cooldown--;
	if (regen_cooldown <= 0) {
		regen_cooldown = REGEN_SLOWDOWN;
		if (health < CRYSTAL_HEALTH) {
			health += REGEN_AMOUNT;
			if (health > CRYSTAL_HEALTH) {
				health = CRYSTAL_HEALTH;
			}
			// Send view event to view.
			df::EventView ev("crystal", health, false);
			WM.onEvent(&ev);
		}
	}
}
