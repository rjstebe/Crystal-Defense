#pragma once
#include "PowerUp.h"

class FireratePowerUp : public PowerUp {
private:
	void hit(const df::EventCollision* p_collision_event) override;
public:
	FireratePowerUp(df::Vector position);
	~FireratePowerUp();
	int eventHandler(const df::Event* p_e);
};


