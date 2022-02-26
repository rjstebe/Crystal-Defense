#include "Enemy.h"

// Engine includes.
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "EventCollision.h"

// Game includes.
#include "EnemyManager.h"
#include "EventDamage.h"

Enemy::Enemy(df::Vector position) {
	setType("Enemy");
	setSprite("enemy");
	setSolidness(df::SOFT);
	setPosition(position);
	target = position;
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
	if (other->getType() == "Crystal" || other->getType() == "Hero") {
		LM.writeLog(-5, "Enemy::hit(): collided with Crystal or Hero");
		if (attack_cooldown <= 0) {
			LM.writeLog(-5, "Enemy::hit(): attacked Crystal or Hero");
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
	
	// Check if crystal or hero is in same room as enemy
	Crystal* crystal = EM.getCrystal();
	Hero* hero = EM.getHero();
	df::Vector crystal_pos = crystal->getPosition();
	df::Vector hero_pos = hero->getPosition();
	Room* current_room = EM.getRoomByPosition(getPosition());
	Room* crystal_room = EM.getRoomByPosition(crystal_pos);
	Room* hero_room = EM.getRoomByPosition(hero_pos);
	// If all are in same room, set target to closer of hero or crystal
	if (current_room != NULL && current_room == hero_room) {
		if (current_room == crystal_room) {
			// If crystal is closer to enemy than hero, set target to crystal
			if (df::Vector(crystal_pos - getPosition()).getMagnitude() <
				df::Vector(hero_pos - getPosition()).getMagnitude()) {
				target = crystal_pos;
			}
			// Otherwise set target to hero
			else {
				target = hero_pos;
			}
		}
		// If hero is in current room but not crystal, set target to hero
		else {
			target = hero_pos;
		}
	}
	else {
		// If hero is not in current room but crystal is, set target to crystal
		if (current_room != NULL && current_room == crystal_room) {
			target = crystal_pos;
		}
		// If hero and crystal are both not in same room as enemy (or enemy is in hallway),
		// Move towards crystal room.
		else {
			if (current_room != NULL) {
				df::Vector exit = current_room->getExitPositionToRoom(crystal_room->getCharName());
				// If at exit, set target to exit of next room
				if (getPosition() == exit) {
					target = crystal_room->getExitPositionToRoom(current_room->getCharName());
				}
				// Otherwise set target to current exit
				else {
					target = exit;
				}
			}
		}
	}

	// Set direction towards target, and speed equal to the enemy's speed
	df::Vector dir = df::Vector(target - getPosition());
	if (dir.getMagnitude() > ENEMY_SPEED) {
		setSpeed(ENEMY_SPEED);
	}
	else {
		setSpeed(dir.getMagnitude());
	}
	dir.normalize();
	setDirection(dir);
}