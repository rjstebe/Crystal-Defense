#pragma once

#include "Object.h"

// Engine includes.
#include "EventCollision.h"
#include "ViewObject.h"

// Game includes.
#include "EventDamage.h"

const int CRYSTAL_HEALTH = 100;
const int REGEN_SLOWDOWN = 150;
const int REGEN_AMOUNT = 1;

class Crystal : public df::Object {
private:
    void damaged(const EventDamage* p_ed);
    void step();
    int health = CRYSTAL_HEALTH;
    int regen_cooldown = 0;
public:
    Crystal(df::Vector position);
    ~Crystal();
    int eventHandler(const df::Event* p_e) override;
};