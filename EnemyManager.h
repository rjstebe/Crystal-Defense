#pragma once

#include <vector>

#include "Manager.h"
#include "ObjectList.h"

#include "Crystal.h"
#include "Hero.h"
#include "Enemy.h"
#include "Room.h"

#define EM EnemyManager::getInstance() // Two-letter acronym.

class EnemyManager : public df::Manager {
private:
	EnemyManager(); // Private (a singleton).
	EnemyManager(EnemyManager const&); // Don't allow copy.
	void operator=(EnemyManager const&); // Don't allow assignment.
	Crystal* p_crystal = NULL; // Pointer to crystal
	Hero* p_hero = NULL; // Pointer to hero
	df::ObjectList rooms; // List of Rooms

public:
	// Get the one and only instance of the EnemyManager.
	static EnemyManager& getInstance();

	// Saves pointers to first crystal and hero it finds.
	// Return 0 if ok, else return -1.
	int startUp();

	// Shut down the enemy manager.
	void shutDown();

	// Get a pointer to the crystal object if it exists.
	Crystal* getCrystal();

	// Get a pointer to the hero object if it exists.
	Hero* getHero();

	// Get a pointer to the room object that a given position is in if it exists. If rooms overlap, returns
	// one of the rooms, which one is chosen depends on the implementation.
	Room* getRoomByPosition(df::Vector position);

	// Get a pointer to the room object associated with the given character if it exists.
	Room* getRoomByChar(char room_name);

	// Adds a new room with a char name, and the given transform, returns -1 if room with that name already
	// exists, 0 otherwise.
	int addRoom(char room_name, df::Box transform);
};

