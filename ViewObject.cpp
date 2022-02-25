#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "ViewObject.h"
#include "EventView.h"
#include "utility.h"

// Construct ViewObject.
// Object settings: SPECTRAL, max alt.
// ViewObject defaults: border, top_center, default color, draw_value.
df::ViewObject::ViewObject() {
	// Initialize Object attributes
	setSolidness(SPECTRAL);
	setAltitude(df::MAX_ALTITUDE);
	setType("ViewObject");
		
	// Initialize ViewObject atttributes.
	setValue(0);
	setDrawValue();
	setBorder(true);
	setLocation(TOP_CENTER);
	setColor(COLOR_DEFAULT);
}

// Return whether object should be drawn when off screen.
bool df::ViewObject::getDrawWhenOffScreen() const {
	return true;
}

// Draw view string and value.
int df::ViewObject::draw() {
	// Display view_string + value.
	std::string temp_str;
	if (m_border) {
		temp_str = " " + view_string + " " + toString(m_value) + " ";
	}
	else {
		temp_str = view_string + " " + toString(m_value);
	}
		
	// Draw centered at position.
	Vector pos = viewToWorld(getPosition());
	DM.drawString(pos, temp_str, CENTER_JUSTIFIED, m_color);
	if (m_border) {
		// Draw box around display.
		std::string width = "+" + std::string(temp_str.size(), '-') + "+";
		DM.drawCh(pos + Vector(-(float)(temp_str.size() + 2) / 2, 0), '|', m_color);
		DM.drawCh(pos + Vector((float)(temp_str.size()) / 2, 0), '|', m_color);
		DM.drawString(pos + Vector(0, 1), width, CENTER_JUSTIFIED, m_color);
		DM.drawString(pos + Vector(0, -1), width, CENTER_JUSTIFIED, m_color);
	}

	return 0;
}

// Handle 'view' event if tag matches view string (others ignored).
// Return 0 if ignored, else 1 if handled.
int df::ViewObject::eventHandler(const Event* p_e) {
	// See if this is 'view' event.
	if (p_e->getType() == VIEW_EVENT) {
		const EventView* p_ve = static_cast<const EventView*>(p_e);
		// See if this event is meant for this object.
		LM.writeLog(-10, "df::ViewObject::eventHandler(): received view event with label: %s, value: %d, delta: %d", p_ve->getTag().c_str(), p_ve->getValue(), p_ve->getDelta());
		if (p_ve->getTag() == getViewString()) {
			if (p_ve->getDelta()) {
				m_value += p_ve->getValue(); // Change in value.
			}
			else {
				m_value = p_ve->getValue(); // New value.
			}
			setLocation(m_location);
			// Event was handled, return ok.
			return 0;
		}
	}
	// If here, event was not handled. Call parent eventHandler().
	Object::eventHandler(p_e);
	return -1;
}

// General location of ViewObject on screen.
void df::ViewObject::setLocation(ViewObjectLocation new_location) {
	// Set new position based on location.
	Vector p = getPosition();
	int y_delta = 0;
	switch (new_location) {
	case TOP_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
		if (!getBorder()) {
			y_delta = -1;
		}
		break;
	case TOP_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
		if (!getBorder()) {
			y_delta = -1;
		}
		break;
	case TOP_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
		if (!getBorder()) {
			y_delta = -1;
		}
		break;
	case CENTER_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() / 2);
		break;
	case CENTER_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() / 2);
		break;
	case CENTER_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() / 2);
		break;
	case BOTTOM_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 2);
		if (!getBorder()) {
			y_delta = 1;
		}
		break;
	case BOTTOM_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 2);
		if (!getBorder()) {
			y_delta = 1;
		}
		break;
	case BOTTOM_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 2);
		if (!getBorder()) {
			y_delta = 1;
		}
		break;
	}
		
	// Shift, as needed, based on border.
	p.setY(p.getY() + y_delta);
		
	// Set position of object to new position.
	setPosition(p);
	LM.writeLog(-10, "ViewObject::setLocation(): set position to: (%f, %f)", p.getX(), p.getY());
		
	// Set new location.
	m_location = new_location;
}

// Get general location of ViewObject on screen.
df::ViewObjectLocation df::ViewObject::getLocation() const {
	return m_location;
}

// Set view value.
void df::ViewObject::setValue(int new_value) {
	m_value = new_value;
}

// Get view value.
int df::ViewObject::getValue() const {
	return m_value;
}

// Set view border (true = display border).
void df::ViewObject::setBorder(bool new_border) {
	if (m_border != new_border) {
		m_border = new_border;

		// Reset location to account for border setting.
		setLocation(m_location);
	}
}

// Get view border (true = display border).
bool df::ViewObject::getBorder() const {
	return m_border;
}

// Set view color.
void df::ViewObject::setColor(Color new_color) {
	m_color = new_color;
}

// Get view color.
df::Color df::ViewObject::getColor() const {
	return m_color;
}

// Set view display string.
void df::ViewObject::setViewString(std::string new_view_string) {
	view_string = new_view_string;
}

// Get view display string.
std::string df::ViewObject::getViewString() const {
	return view_string;
}

// Set true to draw value with display string.
void df::ViewObject::setDrawValue(bool new_draw_value) {
	m_draw_value = new_draw_value;
}

// Get draw value (true if draw value with display string).
bool df::ViewObject::getDrawValue() const {
	return m_draw_value;
}