#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <sstream>

#include "utility.h"
#include "WorldManager.h"
#include "Object.h"

// Return a time string in the format: HH:MM:SS
char* df::getTimeString() {

	// String to return
	static char time_str[30];

	// System calls for getting the time.
	time_t now;
	time(&now);
	struct tm* p_time = localtime(&now);

	// Use sprintf to format time as a string
	sprintf(time_str, "%02d:%02d:%02d",
		p_time->tm_hour,
		p_time->tm_min,
		p_time->tm_sec);
	return time_str;
}

// Return true if two positions intersect, else false.
bool df::positionsIntersect(Vector p1, Vector p2) {
	return abs(p1.getX() - p2.getX()) <= 1 && abs(p1.getY() - p2.getY()) <= 1;
}

// Return true if boxes intersect, else false.
bool df::boxIntersectsBox(Box A, Box B) {
	// Test horizontal overlap (x overlap).
	float Bx1 = B.getCorner().getX();
	float Bx2 = Bx1 + B.getHorizontal();
	float Ax1 = A.getCorner().getX();
	float Ax2 = Ax1 + A.getHorizontal();
	// Either left side of A in B or left side of B in A?
	bool x_overlap = (Bx1 <= Ax1 && Ax1 <= Bx2) || (Ax1 <= Bx1 && Bx1 <= Ax2);

	// Test vertical overlap (y overlap).
	float By1 = B.getCorner().getY();
	float By2 = By1 + B.getVertical();
	float Ay1 = A.getCorner().getY();
	float Ay2 = Ay1 + A.getVertical();
	// Either top side of A in B or top side of B in A?
	bool y_overlap = (By1 <= Ay1 && Ay1 <= By2) || (Ay1 <= By1 && By1 <= Ay2);

	return x_overlap && y_overlap;
}

// Convert relative bounding Box for Object to absolute world Box.
df::Box df::getWorldBox(const Object* p_o) {
	Box temp_box = p_o->getBox();
	Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + p_o->getPosition().getX());
	corner.setY(corner.getY() + p_o->getPosition().getY());
	temp_box.setCorner(corner);

	return temp_box;
}

// Convert world position to view position.
df::Vector df::worldToView(Vector world_pos) {
	Vector view_origin = WM.getView().getCorner();
	return world_pos + !view_origin;
}

// Convert view position to world position.
df::Vector df::viewToWorld(Vector view_pos) {
	Vector view_origin = WM.getView().getCorner();
	return view_pos + view_origin;
}

// Convert int to a string, returning string.
std::string df::toString(int i) {
	using std::stringstream;
	std::stringstream ss; // Create string stream.
	ss << i; // Add number to stream.
	return ss.str(); // Return string with contents of stream.
}

