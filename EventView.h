#pragma once
#include "Event.h"

namespace df {

const std::string VIEW_EVENT = "df::view";

class EventView : public Event {
private:
	std::string m_tag = "VIEW EVENT"; // Tag to associate.
	int m_value = 0;                  // Value for view.
	bool m_delta = false;             // True if change in value, else replace value.

public:
	// Create view event with tag VIEW EVENT, value 0 and delta false.
	EventView();

	// Create view event with tag, value and delta indicated.
	EventView(std::string new_tag, int new_value, bool new_delta);

	// Set tag to new tag.
	void setTag(std::string new_tag);

	// Get tag.
	std::string getTag() const;

	// Set value to new value.
	void setValue(int new_value);

	// Get value.
	int getValue() const;

	// Set delta to new delta.
	void setDelta(bool new_delta);

	// Get delta.
	bool getDelta() const;
};

}