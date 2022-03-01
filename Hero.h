#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"

#include "EventDamage.h"
#include "Reticle.h"

const int PLAYER_HEALTH = 10;
const float INITIAL_FIRE_SLOWDOWN = 15;
const float MOVE_SPEED = 0.5;
const int RESPAWN_TIME = 75;

class Hero : public df::Object {
private:
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void step();
	void fire(df::Vector target);
	void mouse(const df::EventMouse* p_mouse_event);
	void damaged(const EventDamage* p_ed);
	int handleMove(df::Vector move);
	Reticle* p_reticle = new Reticle;
	float move_speed = MOVE_SPEED;
	float fire_slowdown = INITIAL_FIRE_SLOWDOWN;
	int fire_countdown = fire_slowdown;
	int max_health = PLAYER_HEALTH;
	int health = max_health;
	bool alive = true;
	int respawn_time = RESPAWN_TIME;
	int respawn_timer;
	df::Vector input;
public:
	Hero(df::Vector position);
	~Hero();
	int eventHandler(const df::Event* p_e) override;
	int firerateUpgrade();
	int healthUpgrade();
};