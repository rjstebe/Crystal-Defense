#include <chrono>

#include "Clock.h"

// Get the current time in microseconds
long int df::Clock::get_current_time() const {
	using namespace std::chrono;
	return time_point_cast<microseconds>(high_resolution_clock::now()).time_since_epoch().count();
}

// Sets previous_time to current time.
df::Clock::Clock() {
	m_previous_time = get_current_time();
}

// Return time elapsed since delta() was last called, -1 if error.
// Resets previous time.
// Units are microseconds.
long int df::Clock::delta() {
	// Get elapsed time, or -1 if error.
	long int result = split();

	// Set previous time to current time if there was no error.
	if (result != -1) {
		m_previous_time = get_current_time();
	}

	return result;
}

// Return time elapsed since delta() was last called, -1 if error.
// Does not reset previous time.
// Units are microseconds.
long int df::Clock::split() const {
	return get_current_time() - m_previous_time;
}
