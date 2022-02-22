#include "Enemy.h"

Enemy::Enemy() {
	setType("Enemy");
	setSprite("enemy");
	df::Vector p(1, 10);
	setPosition(p);
}
Enemy::~Enemy() {

}

int Enemy::eventHandler(const df::Event* p_e)
{
	return 0;
}
void Enemy::hit(const df::EventCollision* p_collision_event)
{
}