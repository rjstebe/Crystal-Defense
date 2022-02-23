#include "Enemy.h"

// Engine includes.
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "EventCollision.h"

// Game includes.
#include "EventDamage.h"

Enemy::Enemy() {
	setType("Enemy");
	setSprite("enemy");
	df::Vector p(1, 10);
	setPosition(p);
}
Enemy::~Enemy() {

}

// Returns 1 if event was handled, else 0.
int Enemy::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_ce = dynamic_cast<const df::EventCollision*>(p_e);
		hit(p_ce);
		return 1;
	}
	return 0;
}

// When colliding with a player or crystal, attack and reset attack cooldown.
void Enemy::hit(const df::EventCollision* p_collision_event) {
	df::Object* other;
	if (p_collision_event->getObject1()->getType() == "Enemy") {
		other = p_collision_event->getObject2();
	}
	else {
		other = p_collision_event->getObject1();
	}
	if (other->getType() == "Crystal") {
		LM.writeLog(-5, "Enemy::hit(): collided with Crystal");
		if (attack_cooldown <= 0) {
			LM.writeLog(-5, "Enemy::hit(): attacked Crystal");
			EventDamage ed;
			other->eventHandler(&ed);
			attack_cooldown = attack_period;
		}
	}
}

// Each step, update cooldowns and move towards crystal
void Enemy::step() {
	// Update cooldowns
	attack_cooldown--;
	// Get crystal
	df::ObjectList crystals = WM.objectsOfType("Crystal");
	// If there is a crystal,
	if (!crystals.isEmpty()) {
		df::ObjectListIterator li = df::ObjectListIterator(&crystals);
		li.first();
		// Set direction towards crystal, and speed equal to the enemy's speed
		df::Vector dir = df::Vector(li.currentObject()->getPosition() - getPosition());
		dir.normalize();
		setDirection(dir);
		setSpeed(speed);
	}
	else {
		LM.writeLog("Enemy::step(): Error: no Crystal in game world.");
	}
}