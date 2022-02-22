#include "Bullet.h"
#include "WorldManager.h"
#include "EventOut.h"


Bullet::Bullet(df::Vector hero_pos) {
	setType("Bullet");
	setSprite("bullet");
	df::Vector p(1, 5);
	setPosition(p);
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

}