#pragma once

#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"

const float ENEMY_SPEED = 0.25;

class Enemy : public df::Object {
private:
    void hit(const df::EventCollision* p_collision_event);
    void step();
    float attack_period = 30;
    float attack_cooldown = attack_period;
    df::Vector target;
public:
    Enemy(df::Vector position);
    ~Enemy();
    int eventHandler(const df::Event* p_e) override;
};