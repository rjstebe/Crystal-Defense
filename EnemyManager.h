#pragma once

#include <vector>
#include <random>

#include "Object.h"
#include "ObjectList.h"

#include "Crystal.h"
#include "Hero.h"
#include "Enemy.h"
#include "Room.h"

#define EM EnemyManager::getInstance()

class EnemyManager : public df::Object {
private:
	EnemyManager(); // Private (a singleton).
	EnemyManager(EnemyManager const&); // Don't allow copy.
	void operator=(EnemyManager const&); // Don't allow assignment.
	void step(); // Process step event to spawn waves of enemies.
	std::default_random_engine rng; // Random engine
	std::uniform_real_distribution<> random_float; // Random distribution
	Crystal* p_crystal = NULL; // Pointer to crystal
	Hero* p_hero = NULL; // Pointer to hero
	df::ObjectList rooms; // List of Rooms
	df::ObjectList spawner_rooms; // List of Rooms that can spawn enemies
	int enemy_count = 8; // Number of enemies in next wave
	int wave_speed = 300; // Number of frames between waves
	int wave_timer = 0; // Number of frames until next wave

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

	// Adds a new room with a char name, and the given transform, returns a pointer to the created room,
	// or NULL if it cannot be added.
	Room* addRoom(char room_name, df::Box transform, bool add_as_spawner);

	// Handle step events for spawning enemies.
	int eventHandler(const df::Event* p_e);
};

