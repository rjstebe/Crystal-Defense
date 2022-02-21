#pragma once

#include <string>

#include "Event.h"

namespace df {

class Manager {
private:
	std::string type = "Manager"; // Manager type identifier
	bool is_started = false;      // True when started successfully

protected:
	// Set type identifier of manager
	void setType(std::string type);

public:
	Manager();          // Constructor used by subclass constructors
	virtual ~Manager(); // Deconstructor used by subclass deconstructors

	// Get type identifier of Manager.
	std::string getType() const;

	// Startup Manager.
	// Return 0 if ok, else negative number.
	virtual int startUp();

	// Shutdown Manager.
	virtual void shutDown();

	// Return true when startUp() was executed ok, else false.
	bool isStarted() const;

	// Send event to all objects.
	// Return count of number of events sent.
	int onEvent(const Event* p_event) const;
};

} // end of namespace df
