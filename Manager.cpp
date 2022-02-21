#include "Manager.h"
#include "WorldManager.h"
#include "ObjectList.h"

// Set type identifier of manager
void df::Manager::setType(std::string type) {
	this->type = type;
}

// Constructor used by subclass constructors
df::Manager::Manager() {}

// Deconstructor used by subclass deconstructors
df::Manager::~Manager() {}

// Get type identifier of Manager.
std::string df::Manager::getType() const {
	return type;
}

// Startup Manager.
// Return 0 if ok, else negative number.
int df::Manager::startUp() {
	is_started = true;
	return 0;
}

// Shutdown Manager.
void df::Manager::shutDown() {
	is_started = false;
}

// Return true when startUp() was executed ok, else false.
bool df::Manager::isStarted() const {
	return is_started;
}

// Send event to all objects.
// Return count of number of events sent.
int df::Manager::onEvent(const df::Event* p_event) const {
	int count = 0;
	df::ObjectList all_objects = WM.getAllObjects();
	df::ObjectListIterator li = df::ObjectListIterator(&all_objects);
	for (li.first(); !li.isDone(); li.next()) {
		li.currentObject()->eventHandler(p_event);
		count++;
	}
	return count;
}
