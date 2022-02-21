#include "Object.h"
#include "Event.h"
#include "WorldManager.h"
#include "ResourceManager.h"

// Construct Object. Set default parameters and
// add to game world (WorldManager).
df::Object::Object() {
	// Get id.
	static int nextInt = 0;
	id = nextInt;
	nextInt++;

	// Set initial altitude.
	m_altitude = MAX_ALTITUDE / 2;

	// Add self to game world.
	WM.insertObject(this);
}

// Destroy Object.
// Remove from game world (WorldManager).
// (Default constructor, can be overridden by subclasses)
df::Object::~Object() {
	// Remove self from game world.
	WM.removeObject(this);
}

// Set object id.
void df::Object::setId(int new_id) {
	id = new_id;
}

// Get object id.
int df::Object::getId() const {
	return id;
}

// Set type identifier of Object.
void df::Object::setType(std::string new_type) {
	type = new_type;
}

// Get type identifier of Object.
std::string df::Object::getType() const {
	return type;
}

// Set position of object.
void df::Object::setPosition(Vector new_pos) {
	pos = new_pos;
}

// Get position of object.
df::Vector df::Object::getPosition() const {
	return pos;
}

// Set speed of Object.
void df::Object::setSpeed(float speed) {
	m_speed = speed;
}

// Get speed of Object.
float df::Object::getSpeed() const {
	return m_speed;
}

// Set direction of Object.
void df::Object::setDirection(Vector new_direction) {
	m_direction = new_direction;
}

// Get direction of Object.
df::Vector df::Object::getDirection() const {
	return m_direction;
}

// Set direction and speed of Object.
void df::Object::setVelocity(Vector new_velocity) {
	m_speed = new_velocity.getMagnitude();
	new_velocity.normalize();
	m_direction = new_velocity;
}

// Get velocity of Object based on direction and speed.
df::Vector df::Object::getVelocity() const {
	Vector velocity = m_direction;
	velocity.scale(m_speed);
	return velocity;
}

// Set acceleration of Object.
void df::Object::setAcceleration(Vector new_acceleration) {
	m_acceleration = new_acceleration;
}

// Get acceleration of Object.
df::Vector df::Object::getAcceleration() const {
	return m_acceleration;
}

// Predict Object position based on speed and direction.
// Return predicted position.
df::Vector df::Object::predictPosition() {
	// Add velocity to position.
	// Return new position.
	return pos + getVelocity();
}

// Set altitude of Object, with checks for range [0, MAX ALTITUDE].
// Return 0 if ok, else -1.
int df::Object::setAltitude(int new_altitude) {
	if (new_altitude < 0 || new_altitude > MAX_ALTITUDE) {
		return -1;
	}
	m_altitude = new_altitude;
	return 0;
}

// Return altitude of Object.
int df::Object::getAltitude() const {
	return m_altitude;
}

// True if HARD or SOFT, else false.
bool df::Object::isSolid() const {
	return m_solidness != SPECTRAL;
}

// Set object solidness, with checks for consistency.
// Return 0 if ok, else -1.
int df::Object::setSolidness(Solidness new_solid) {
	m_solidness = new_solid;
	return 0;
}

// Return object solidness.
df::Solidness df::Object::getSolidness() const {
	return m_solidness;
}

// Set Sprite for this Object to animate.
// Return 0 if ok, else -1.
int df::Object::setSprite(std::string sprite_label) {
	Sprite* p_temp_sprite = RM.getSprite(sprite_label);
	if (p_temp_sprite == NULL) {
		return -1;
	}

	m_animation.setSprite(p_temp_sprite);
	m_box = m_animation.getBox();
	// All is well.
	return 0;
}

// Set Animation for this Object to new one.
// Set bounding box to size of associated Sprite.
void df::Object::setAnimation(Animation new_animation) {
	m_animation = new_animation;
}

// Get Animation for this Object.
df::Animation df::Object::getAnimation() const {
	return m_animation;
}

// Set Object's bounding box.
void df::Object::setBox(Box new_box) {
	m_box = new_box;
}

// Get Object's bounding box.
df::Box df::Object::getBox() const {
	return m_box;
}

// Handle event (default is to ignore everything).
// Return 0 if ignored, else 1 if handled.
int df::Object::eventHandler(const df::Event* p_e) {
	return 0;
}

// Draw Object Animation.
// Return 0 if ok, else -1.
int df::Object::draw() {
	return m_animation.draw(pos);
}
