#include "Animation.h"
#include "LogManager.h"

// Animation constructor
df::Animation::Animation() {}

// Set associated Sprite to new one.
// Note, Sprite is managed by ResourceManager.
// Set Sprite index to 0 (first frame).
void df::Animation::setSprite(Sprite* p_new_sprite) {
	m_p_sprite = p_new_sprite;
}

// Return pointer to associated Sprite.
df::Sprite* df::Animation::getSprite() const {
	return m_p_sprite;
}

// Set Sprite name (in ResourceManager).
void df::Animation::setName(std::string new_name) {
	m_name = new_name;
}

// Get Sprite name (in ResourceManager).
std::string df::Animation::getName() const {
	return m_name;
}

// Get bounding box of associated Sprite.
df::Box df::Animation::getBox() const {
	// If no Sprite, return unit Box centered at (0, 0).
	if (m_p_sprite == NULL) {
		Box box(Vector(-0.5, -0.5), 0.99, 0.99);
		return box;
	}

	// Create Box around centered Sprite.
	Vector corner(-1 * m_p_sprite->getWidth() / 2.0, -1 * m_p_sprite->getHeight() / 2.0);
	// Return box.
	return Box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());
}

// Set index of current Sprite frame to be displayed.
void df::Animation::setIndex(int new_index) {
	m_index = new_index;
}

// Get index of current Sprite frame to be displayed.
int df::Animation::getIndex() const {
	return m_index;
}

// Set animation slowdown count (-1 means stop animation).
void df::Animation::setSlowdownCount(int new_slowdown_count) {
	m_slowdown_count = new_slowdown_count;
}

// Get animation slowdown count (-1 means stop animation).
int df::Animation::getSlowdownCount() const {
	return m_slowdown_count;
}

// Draw single frame centered at position (x, y).
// Drawing accounts for slowdown, and advance Sprite frame.
// Return 0 if ok, else -1.
int df::Animation::draw(Vector position) {
	// If sprite not defined, don't continue further.
	if (m_p_sprite == NULL) {
		return -1;
	}
	LM.writeLog(-20, "Animation::draw(): index: %d, slowdown_count: %d", m_index, m_slowdown_count);
		
	// Ask Sprite to draw current frame.
	m_p_sprite->draw(m_index, position);
		
	// If slowdown count is -1, then animation is frozen.
	if (m_slowdown_count < 0) {
		return 0;
	}
		
	// Increment counter.
	m_slowdown_count++;
	// Advance sprite index, if appropriate.
	if (m_slowdown_count >= m_p_sprite->getSlowdown()) {
		m_slowdown_count = 0; // Reset counter.
		m_index++; // Advance frame.
		// If at last frame, loop to beginning.
		if (m_index >= m_p_sprite->getFrameCount()) {
			m_index = 0;
		}
	}
}
