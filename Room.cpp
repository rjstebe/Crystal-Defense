#include "Room.h"

#include "LogManager.h"
#include "DisplayManager.h"

#include "EnemyManager.h"

// Initialize the transform and char name of the room
Room::Room(char new_name, df::Box new_transform) {
	name = new_name;
	transform = new_transform;
	setType("Room");
	setSolidness(df::SPECTRAL);
}

// Get the position of the exit in this room that an enemy must take to reach the room with the given
// char name. Should only be called if a route to the given room has definitely been established as there
// is no error checking, and will otherwise throw an unhandled exception.
df::Vector Room::getExitPositionToRoom(char room_name) {
	return director_map[room_name];
}

// Returns whether the given position is within the confines of the room.
bool Room::isInRoom(df::Vector position) {
	df::Vector corner = transform.getCorner();
	float roomX = corner.getX();
	float roomY = corner.getY();
	float x = position.getX();
	float y = position.getY();
	if (roomX <= x && roomX + transform.getHorizontal() >= x &&
		roomY <= y && roomY + transform.getVertical() >= y) {
		return true;
	}
	return false;
}

// Returns the character associated with the room.
char Room::getCharName() {
	return name;
}

// Add a route from this room to another by associating the other room's char name with an exit location
// in this room. This must be done for indirect connections as well. Returns -1 if unsuccessful, 0
// otherwise.
int Room::addRoute(char room_name, df::Vector exit_position) {
	if (room_name == name) {
		return -1;
	}

	if (EM.getRoomByChar(room_name) == NULL) {
		return -1;
	}

	director_map[room_name] = exit_position;
	LM.writeLog(-10, "Added connection from room %s to room %s via (%f, %f)", std::string(1, name).c_str(), std::string(1, room_name).c_str(), exit_position.getX(), exit_position.getY());
}

// Draw for testing room positions
int Room::draw() {
	// Draw debug cursors at four corners of room
	DM.drawCh(transform.getCorner(), '+', df::MAGENTA);
	DM.drawCh(transform.getCorner() + df::Vector(transform.getHorizontal(), 0), '+', df::MAGENTA);
	DM.drawCh(transform.getCorner() + df::Vector(0, transform.getVertical()), '+', df::MAGENTA);
	DM.drawCh(transform.getCorner() + df::Vector(transform.getHorizontal(), transform.getVertical()), '+', df::MAGENTA);
	
	// Draw character for each connection to another room
	std::map<char, df::Vector>::iterator it;
	for (it = director_map.begin(); it != director_map.end(); it++)
	{
		DM.drawCh(it->second, it->first, df::WHITE);
	}
	return 0;
}
