#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"

#include "EventDamage.h"
#include "Reticle.h"

const int PLAYER_HEALTH = 10;

class Hero : public df::Object {
private:
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void step();
	void fire(df::Vector target);
	void mouse(const df::EventMouse* p_mouse_event);
	void damaged(const EventDamage* p_ed);
	int handleMove(df::Vector move);
	Reticle* p_reticle = new Reticle;
	float move_speed = 0.5;
	int fire_slowdown = 15;
	int fire_countdown = fire_slowdown;
	int max_health = PLAYER_HEALTH;
	int health = max_health;
	bool alive = true;
	int respawn_time = 150;
	int respawn_timer;
	df::Vector input;
public:
	Hero(df::Vector position);
	~Hero();
	int eventHandler(const df::Event* p_e) override;
	int firerateUpgrade();
	int healthUpgrade();
};