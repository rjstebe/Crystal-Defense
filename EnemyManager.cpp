#include "EnemyManager.h"

#include "WorldManager.h"
#include "ObjectListIterator.h"

// Called only by getInstance().
EnemyManager::EnemyManager() {}

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

	return Manager::startUp();
}

// Shut down the enemy manager.
void EnemyManager::shutDown() {
	Manager::shutDown();
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

// Adds a new room with a char name, and the given transform, returns -1 if room with that name already
// exists, or insert fails, 0 otherwise.
int EnemyManager::addRoom(char room_name, df::Box transform) {
	if (getRoomByChar(room_name) != NULL) {
		return -1;
	}
	return rooms.insert(new Room(room_name, transform));
}
