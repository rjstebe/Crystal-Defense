#pragma once

#include "EnemyManager.h"

#include <random>

#include "LogManager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"

// Called only by getInstance().
EnemyManager::EnemyManager() {
	setSolidness(df::SPECTRAL);
	setType("EnemyManager");
}

// Get the one and only instance of the InputManager.
EnemyManager& EnemyManager::getInstance() {
	static EnemyManager& instance = *new EnemyManager();
	return instance;
}

// Saves pointers to first crystal and hero it finds.
// Return 0 if ok, else return -1.
int EnemyManager::startUp() {
	// If WorldManager has not set up objects yet, return -1.
	if (!WM.isStarted()) {
		return -1;
	}
	// Get Crystal and Hero (if cannot find either, return -1).
	df::ObjectList crystals = WM.objectsOfType("Crystal");
	df::ObjectList heros = WM.objectsOfType("Hero");
	df::ObjectListIterator crystals_iter = df::ObjectListIterator(&crystals);
	df::ObjectListIterator heros_iter = df::ObjectListIterator(&heros);
	crystals_iter.first();
	heros_iter.first();
	// If there are no crystals or no heros, fail to start up.
	if (crystals_iter.isDone() || heros_iter.isDone()) {
		return -1;
	}
	p_crystal = dynamic_cast<Crystal*>(crystals_iter.currentObject());
	p_hero = dynamic_cast<Hero*>(heros_iter.currentObject());
	enemy_count = 8;
	wave_timer = 0;
	// Start RNG
	random_float = std::uniform_real_distribution<>(0, 1);

	is_started = 1;

	return 0;
}

// Shut down the enemy manager.
void EnemyManager::shutDown() {
	is_started = 0;
}

// Get a pointer to the crystal object if it exists.
Crystal* EnemyManager::getCrystal() {
	return p_crystal;
}

// Get a pointer to the hero object if it exists.
Hero* EnemyManager::getHero() {
	return p_hero;
}

// Get a pointer to the room object that a given position is in if it exists. If rooms overlap, returns one
// of the rooms, which one is chosen depends on the implementation.
Room* EnemyManager::getRoomByPosition(df::Vector position) {
	df::ObjectListIterator li = df::ObjectListIterator(&rooms);
	for (li.first(); !li.isDone(); li.next()) {
		Room* currentRoom = dynamic_cast<Room*>(li.currentObject());
		if (currentRoom->isInRoom(position)) {
			return currentRoom;
		}
	}
	return NULL;
}

// Get a pointer to the room object associated with the given character if it exists.
Room* EnemyManager::getRoomByChar(char room_name) {
	df::ObjectListIterator li = df::ObjectListIterator(&rooms);
	for (li.first(); !li.isDone(); li.next()) {
		Room* currentRoom = dynamic_cast<Room*>(li.currentObject());
		if (currentRoom->getCharName() == room_name) {
			return currentRoom;
		}
	}
	return NULL;
}

// Adds a new room with a char name, and the given transform, returns a pointer to the created room,
// or NULL if it cannot be added.
Room* EnemyManager::addRoom(char room_name, df::Box transform, bool add_as_spawner) {
	if (getRoomByChar(room_name) != NULL) {
		return NULL;
	}
	Room* p_room = new Room(room_name, transform);
	int a = rooms.insert(p_room);
	if (a != 0) {
		return NULL;
	}
	if (add_as_spawner) {
		spawner_rooms.insert(p_room);
	}
	return p_room;
}

// Handle step events for spawning enemies.
int EnemyManager::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

// Process step event to spawn waves of enemies.
void EnemyManager::step() {
	if (is_started) {


	wave_timer--;
	if (wave_timer <= 0) {
		LM.writeLog(0, "EnemyManager::step(): New wave released! spawning enemies in %d rooms", spawner_rooms.getCount());
		wave_timer = WAVE_SPEED;
		df::ObjectListIterator li = df::ObjectListIterator(&spawner_rooms);
		for (li.first(); !li.isDone(); li.next()) {
			Room* spawner_room = dynamic_cast<Room*>(li.currentObject());
			for (int i = 0; i < enemy_count / spawner_rooms.getCount(); i++) {
				df::Box spawner_area = spawner_room->getTransform();
				float x = random_float(rng) * spawner_area.getHorizontal() + spawner_area.getCorner().getX();
				float y = random_float(rng) * spawner_area.getVertical() + spawner_area.getCorner().getY();
				new Enemy(df::Vector(x, y));
			}
		}
		enemy_count = (float)enemy_count * WAVE_GROWTH;
	}
	}
}
