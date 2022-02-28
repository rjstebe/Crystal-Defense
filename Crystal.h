#pragma once

#include "Object.h"

// Engine includes.
#include "EventCollision.h"
#include "ViewObject.h"

// Game includes.
#include "EventDamage.h"

const int CRYSTAL_HEALTH = 100;

class Crystal : public df::Object {
private:
    void damaged(const EventDamage* p_ed);
    int health = CRYSTAL_HEALTH;
public:
    Crystal(df::Vector position);
    ~Crystal();
    int eventHandler(const df::Event* p_e) override;
};