#pragma once
#include "PowerUp.h"

class HealthPowerUp : public PowerUp {
private:
	void hit(const df::EventCollision* p_collision_event) override;
public:
	HealthPowerUp(df::Vector position);
	~HealthPowerUp();
	int eventHandler(const df::Event* p_e);
};

