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
	void move(int dx, int dy);
	float move_speed = 0.5;
	int fire_slowdown = 15;
	int fire_countdown = fire_slowdown;
	int health_count = PLAYER_HEALTH;
	void step();
	void fire(df::Vector target);
	void mouse(const df::EventMouse* p_mouse_event);
	void damaged(const EventDamage* p_ed);
	void hit(const df::EventCollision* p_collision_event);
	Reticle* p_reticle = new Reticle;
	int handleMove(df::Vector move);
	int n;
	int s;
	int e;
	int w;
public:
	Hero();
	~Hero();
	int eventHandler(const df::Event* p_e) override;
	int firerateUpgrade();
};