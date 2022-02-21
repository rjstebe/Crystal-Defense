#pragma once

#include <SFML/Window/Mouse.hpp>

#include "Event.h"
#include "Vector.h"

namespace df {

const std::string MSE_EVENT = "df::mouse";

// Set of mouse actions recognized by Dragonfly.
enum EventMouseAction {
	UNDEFINED_MOUSE_ACTION = -1,
	CLICKED,
	PRESSED,
	MOVED,
};

// Set of mouse buttons recognized by Dragonfly.
namespace Mouse {
	enum Button {
		UNDEFINED_MOUSE_BUTTON = -1,
		LEFT,
		RIGHT,
		MIDDLE,
	};
} // end of namespace Mouse

class EventMouse : public Event {
	
private:
	EventMouseAction m_mouse_action = UNDEFINED_MOUSE_ACTION; // Mouse action.
	Mouse::Button m_mouse_button = Mouse::UNDEFINED_MOUSE_BUTTON; // Mouse button.
	Vector m_mouse_xy; // Mouse (x, y) coordinates.
		
public:
	EventMouse();
	
	// Load mouse event's action.
	void setMouseAction(EventMouseAction new_mouse_action);
	
	// Get mouse event's action.
	EventMouseAction getMouseAction() const;
	
	// Set mouse event's button.
	void setMouseButton(Mouse::Button new_mouse_button);
	
	// Get mouse event's button.
	Mouse::Button getMouseButton() const;
	
	// Set mouse event's position.
	void setMousePosition(Vector new_mouse_xy);
	
	// Get mouse event's position
	Vector getMousePosition() const;
};

// Convert SFML mouse button codes to Dragonfly EventMouseAction
Mouse::Button SFMLMouseButtonToDFMouseButton(sf::Mouse::Button sfml_key_event);

}
