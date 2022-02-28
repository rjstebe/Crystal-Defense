#include "Bullet.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "ResourceManager.h"


Bullet::Bullet(df::Vector hero_pos) {
	setType("Bullet");
	setSprite("bullet");
	df::Vector p(hero_pos.getX(), hero_pos.getY());
	setPosition(p);
	setSpeed(1);
	setSolidness(df::SOFT);
}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

// If Bullet moves outside world, mark self for deletion.
void Bullet::out() {
	WM.markForDelete(this);
}

void Bullet::hit(const df::EventCollision* p_collision_event) {
	if (((p_collision_event->getObject1()->getType() == "Enemy") ||
		(p_collision_event->getObject2()->getType() == "Enemy")) &&
		!hit_enemy) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
		hit_enemy = true;
		df::Sound* p_sound = RM.getSound("enemydeath");
		p_sound->play();
	}
	if ((p_collision_event->getObject1()->getType() == "Wall") ||
		(p_collision_event->getObject2()->getType() == "Wall")) {
		if ((p_collision_event->getObject1()->getType()) == "Bullet") {
			WM.markForDelete(p_collision_event->getObject1());
		}
		else {
			WM.markForDelete(p_collision_event->getObject2());
		}
	}
}