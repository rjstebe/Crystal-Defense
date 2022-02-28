#include "FireratePowerUp.h"

// Engine includes.
#include "LogManager.h"

// Game includes.
#include "EventDamage.h"
#include "Hero.h"

FireratePowerUp::FireratePowerUp(df::Vector position) : PowerUp(position) {
	setType("Firerate Power Up");
	setSprite("fireratepowerup");
	setSolidness(df::SOFT);
}

FireratePowerUp::~FireratePowerUp() {

}

int FireratePowerUp::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_ec = dynamic_cast<const df::EventCollision*>(p_e);
		hit(p_ec);
		return 0;
	}
	return -1;
}

void FireratePowerUp::hit(const df::EventCollision* p_collision_event) {
	df::Object* other;
	if (p_collision_event->getObject1()->getType() == getType()) {
		other = p_collision_event->getObject2();
	}
	else {
		other = p_collision_event->getObject1();
	}
	if (other->getType() == "Hero") {
		LM.writeLog("FireratePowerUp::hit(): player picked up firerate powerup");
		Hero* hero = dynamic_cast<Hero*>(other);
		hero->firerateUpgrade();
		delete this;
	}
}
