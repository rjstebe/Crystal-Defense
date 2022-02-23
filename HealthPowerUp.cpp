#include "HealthPowerUp.h"

// Engine includes.
#include "LogManager.h"

// Game includes.
#include "EventDamage.h"
#include "Hero.h"

HealthPowerUp::HealthPowerUp() {
	setType("Health Power Up");
	setSprite("healthpowerup");
	setSolidness(df::SOFT);
	df::Vector p(20, 20);
	setPosition(p);
}

HealthPowerUp::~HealthPowerUp() {

}

int HealthPowerUp::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_ec = dynamic_cast<const df::EventCollision*>(p_e);
		hit(p_ec);
		return 0;
	}
	return -1;
}

void HealthPowerUp::hit(const df::EventCollision* p_collision_event) {
	df::Object* other;
	if (p_collision_event->getObject1()->getType() == getType()) {
		other = p_collision_event->getObject2();
	}
	else {
		other = p_collision_event->getObject1();
	}
	if (other->getType() == "Hero") {
		LM.writeLog("HealthPowerUp::hit(): player picked up health powerup");
		EventDamage ed(-PLAYER_HEALTH / 5);
		other->eventHandler(&ed);
		delete this;
	}
}