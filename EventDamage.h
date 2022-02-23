#pragma once
#include "Event.h"

const std::string DAMAGE_EVENT = "damage";

class EventDamage : public df::Event {
private:
	int damage = 1;

public:
	// Default constructor
	EventDamage();

	// Constructor with specified damage value
	EventDamage(int new_damage);

	// Set damage
	void setDamage(int new_damage);

	// Get damage
	int getDamage() const;
};

