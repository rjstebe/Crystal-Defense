#include "Sprite.h"
#include "LogManager.h"

// Destroy sprite, deleting any allocated frames.
df::Sprite::~Sprite() {
	if (m_frame != NULL) {
		delete[] m_frame;
	}
}

// Create sprite with indicated maximum number of frames.
df::Sprite::Sprite(int max_frames) {
	m_frame = new Frame[max_frames];
	if (m_frame == NULL) {
		m_max_frame_count = 0;
		LM.writeLog("Sprite::Sprite(): Cannot allocate array of %d frames", max_frames);
	}
	else {
		m_max_frame_count = max_frames;
	}
}

// Set width of sprite.
void df::Sprite::setWidth(int new_width) {
	m_width = new_width;
}

// Get width of sprite.
int df::Sprite::getWidth() const {
	return m_width;
}

// Set height of sprite.
void df::Sprite::setHeight(int new_height) {
	m_height = new_height;
}

// Get height of sprite.
int df::Sprite::getHeight() const {
	return m_height;
}

// Set sprite color.
void df::Sprite::setColor(Color new_color) {
	m_color = new_color;
}

// Get sprite color.
df::Color df::Sprite::getColor() const {
	return m_color;
}

// Get total count of frames in sprite.
int df::Sprite::getFrameCount() const {
	return m_frame_count;
}

// Add frame to sprite.
// Return -1 if frame array full, else 0.
int df::Sprite::addFrame(Frame new_frame) {
	if (m_frame_count >= m_max_frame_count) { // Is Sprite full?
		LM.writeLog("Sprite::addFrame(): cannot add another frame to sprite with max frame count of %d", m_max_frame_count);
		return -1;
	}
	m_frame[m_frame_count] = new_frame;
	m_frame_count++;
	return 0;
}

// Get next sprite frame indicated by number.
// Return empty frame if out of range [0, m_frame_count-1].
df::Frame df::Sprite::getFrame(int frame_number) const {
	if (frame_number < 0 || frame_number >= m_frame_count) {
		return Frame(); // Make empty frame and return it.
	}
	return m_frame[frame_number];
}

// Set label associated with sprite.
void df::Sprite::setLabel(std::string new_label) {
	m_label = new_label;
}

// Get label associated with sprite.
std::string df::Sprite::getLabel() const {
	return m_label;
}

// Set animation slowdown value.
// Value in multiples of GameManager frame time.
void df::Sprite::setSlowdown(int new_sprite_slowdown) {
	m_slowdown = new_sprite_slowdown;
}

// Get animation slowdown value.
// Value in multiples of GameManager frame time.
int df::Sprite::getSlowdown() const {
	return m_slowdown;
}

// Draw indicated frame centered at position (x, y).
// Return 0 if ok, else -1.
// Note: top-left coordinate is (0, 0).
int df::Sprite::draw(int frame_number, Vector position) const {
	return getFrame(frame_number).draw(position, m_color);
}
