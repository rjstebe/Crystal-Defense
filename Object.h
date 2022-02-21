#pragma once

#include <string>

#include "Vector.h"
#include "Box.h"
#include "Animation.h"
#include "Event.h"

namespace df {

enum Solidness {
	HARD, // Object causes collisions and impedes.
	SOFT, // Object causes collisions, but doesn't impede.
	SPECTRAL, // Object doesn't cause collisions.
};

class Object {
private:
	int id;                         // Unique Object identifier.
	std::string type = "undefined"; // User-defined identification.
	Vector pos = Vector();            // Position in game world.
	Vector m_acceleration = Vector(); // Acceleration vector.
	Vector m_direction = Vector(1,0); // Direction vector.
	float m_speed = 0;                // Object speed in direction.
	int m_altitude;                                  // 0 to MAX supported (lower drawn first).
	Solidness m_solidness = HARD;                    // Solidness of Object.
	Animation m_animation;                           // Animation associated with Object.
	Box m_box = Box(Vector(-0.5, -0.5), 0.99, 0.99); // Box for sprite boundary & collisions.

public:
	// Construct Object. Set default parameters and
	// add to game world (WorldManager).
	Object();

	// Destroy Object.
	// Remove from game world (WorldManager).
	virtual ~Object();

	// Set Object id.
	void setId(int new_id);

	// Get Object id.
	int getId() const;

	// Set type identifier of Object.
	void setType(std::string new_type);

	// Get type identifier of Object.
	std::string getType() const;

	// Set position of Object.
	void setPosition(Vector new_pos);

	// Get position of Object.
	Vector getPosition() const;

	// Set speed of Object.
	void setSpeed(float speed);
	
	// Get speed of Object.
	float getSpeed() const;
	
	// Set direction of Object.
	void setDirection(Vector new_direction);
	
	// Get direction of Object.
	Vector getDirection() const;
	
	// Set direction and speed of Object.
	void setVelocity(Vector new_velocity);
		
	// Get velocity of Object based on direction and speed.
	Vector getVelocity() const;

	// Set acceleration of Object.
	void setAcceleration(Vector new_acceleration);

	// Get acceleration of Object.
	Vector getAcceleration() const;
	
	// Predict Object position based on speed and direction.
	// Return predicted position.
	Vector predictPosition();

	// Set altitude of Object, with checks for range [0, MAX ALTITUDE].
	// Return 0 if ok, else -1.
	int setAltitude(int new_altitude);
	
	// Return altitude of Object.
	int getAltitude() const;

	// True if HARD or SOFT, else false.
	bool isSolid() const;

	// Set object solidness, with checks for consistency.
	// Return 0 if ok, else -1.
	int setSolidness(Solidness new_solid);

	// Return object solidness.
	Solidness getSolidness() const;

	// Set Sprite for this Object to animate.
	// Return 0 if ok, else -1.
	int setSprite(std::string sprite_label);

	// Set Animation for this Object to new one.
	// Set bounding box to size of associated Sprite.
	void setAnimation(Animation new_animation);

	// Get Animation for this Object.
	Animation getAnimation() const;

	// Set Object's bounding box.
	void setBox(Box new_box);
	
	// Get Object's bounding box.
	Box getBox() const;

	// Handle event (default is to ignore everything).
	// Return 0 if ignored, else 1 if handled.
	virtual int eventHandler(const Event * p_e);

	// Draw Object Animation.
	// Return 0 if ok, else -1.
	virtual int draw();
};

}
