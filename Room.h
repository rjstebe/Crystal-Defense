#pragma once

#include "ViewObject.h"

#include <map>

class Room : public df::ViewObject{
private:
	df::Box transform; // Position and size of the room
	char name; // Character associated with the room
	// Maps a room's name to the location in this room that corresponds to the exit the enemy must take
	// to get to that room.
	std::map<char, df::Vector> director_map;
public:
	// Initialize the transform and char name of the room
	Room(char name, df::Box transform);

	// Get the position of the exit in this room that an enemy must take to reach the room with the given
	// char name.
	df::Vector getExitPositionToRoom(char room_name);

	// Returns whether the given position is within the confines of the room.
	bool isInRoom(df::Vector position);

	// Returns the character associated with the room.
	char getCharName();

	// Returns the box transform of the room.
	df::Box getTransform();

	// Add a route from this room to another by associating the other room's char name with an exit location
	// in this room. This must be done for indirect connections as well. Returns -1 if unsuccessful, 0
	// otherwise.
	int addRoute(char room_name, df::Vector exit_position);

	// Draw for testing room positions
	int draw() override;
};

