#include "Frame.h"
#include "DisplayManager.h"

// Create empty frame.
df::Frame::Frame() {}

// Create frame of indicated width and height with string.
df::Frame::Frame(int new_width, int new_height, std::string frame_str) {
	m_width = new_width;
	m_height = new_height;
	m_frame_str = frame_str;
}

// Set width of frame.
void df::Frame::setWidth(int new_width) {
	m_width = new_width;
}

// Get width of frame.
int df::Frame::getWidth() const {
	return m_width;
}

// Set height of frame.
void df::Frame::setHeight(int new_height) {
	m_height = new_height;
}

// Get height of frame.
int df::Frame::getHeight() const {
	return m_height;
}

// Set frame characters (stored as string).
void df::Frame::setString(std::string new_frame_str) {
	m_frame_str = new_frame_str;
}

// Get frame characters (stored as string).
std::string df::Frame::getString() const {
	return m_frame_str;
}

// Draw self, centered at position (x, y) with color.
// Return 0 if ok, else -1.
// Note: top-left coordinate is (0, 0).
int df::Frame::draw(Vector position, Color color) const {
	// Error check empty string.
	if (m_frame_str.empty()) {
		return -1;
	}
		
	// Determine offset since centered at position.
	float x_offset = getWidth() / 2;
	float y_offset = getHeight() / 2;
		
	// Draw character by character.
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			Vector temp_pos(position.getX() + x - x_offset, position.getY() + y - y_offset);
			DM.drawCh(temp_pos, m_frame_str[y * m_width + x], color);
		} // x
	} // y
}
