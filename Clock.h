#pragma once

// The clock, for timing (such as in the game loop).

namespace df {

class Clock {
private:
	long int get_current_time() const; // Get the current time in microseconds
	long int m_previous_time;    // Previous time delta() called (in microsec).

public:
	// Sets previous_time to current time.
	Clock();

	// Return time elapsed since delta() was last called, -1 if error.
	// Resets previous time.
	// Units are microseconds.
	long int delta();

	// Return time elapsed since delta() was last called, -1 if error.
	// Does not reset previous time.
	// Units are microseconds.
	long int split() const;
};

}
