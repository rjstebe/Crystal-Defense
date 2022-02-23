#include "EventDamage.h"

// Default constructor
EventDamage::EventDamage() {
	setType(DAMAGE_EVENT);
}

// Constructor with specified damage value
EventDamage::EventDamage(int new_damage) {
	setType(DAMAGE_EVENT);
	damage = new_damage;
}

// Set damage
void EventDamage::setDamage(int new_damage) {
	damage = new_damage;
}

// Get damage
int EventDamage::getDamage() const{
	return damage;
}
