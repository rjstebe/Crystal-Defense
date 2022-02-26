#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "utility.h"

#include <iostream>

// Called only by getInstance().
df::WorldManager::WorldManager() {}

// Get the one and only instance of the WorldManager.
df::WorldManager& df::WorldManager::getInstance() {
	static df::WorldManager& instance = *new WorldManager();
	return instance;
}

// Start up game world (initialize everything to empty).
// Return 0.
int df::WorldManager::startUp() {
	setType("WorldManager");
	p_view_following = NULL;
	boundary = Box(Vector(), WINDOW_HORIZONTAL_CHARS_DEFAULT, WINDOW_VERTICAL_CHARS_DEFAULT);
	view = Box(Vector(), WINDOW_HORIZONTAL_CHARS_DEFAULT, WINDOW_VERTICAL_CHARS_DEFAULT);
	return df::Manager::startUp();
}

// Shutdown game world (delete all game world Objects).
void df::WorldManager::shutDown() {
	// Delete all game objects
	ObjectList ol = m_updates;
	ObjectListIterator li = ObjectListIterator(&ol);
	for (li.first(); !li.isDone(); li.next()) {
		delete li.currentObject();
	}
	m_updates.clear();
	m_deletions.clear();

	df::Manager::shutDown();
}

// Set game world boundary.
void df::WorldManager::setBoundary(Box new_boundary) {
	boundary = new_boundary;
}

// Get game world boundary.
df::Box df::WorldManager::getBoundary() const {
	return boundary;
}

// Set player view of game world.
void df::WorldManager::setView(Box new_view) {
	view = new_view;
}

// Get player view of game world.
df::Box df::WorldManager::getView() const {
	return view;
}

// Set view to center window on position view_pos.
// View edge will not go beyond world boundary.
void df::WorldManager::setViewPosition(Vector view_pos) {
	// Make sure horizontal not out of world boundary.
	float x = view_pos.getX() - view.getHorizontal() / 2;
	if (x > boundary.getCorner().getX() + boundary.getHorizontal() - view.getHorizontal()) {
		x = boundary.getCorner().getX() + boundary.getHorizontal() - view.getHorizontal();
	}
	if (x < boundary.getCorner().getX()) {
		x = boundary.getCorner().getX();
	}
	// Make sure vertical not out of world boundary.
	float y = view_pos.getY() - view.getVertical() / 2;
	if (y > boundary.getCorner().getY() + boundary.getVertical() - view.getVertical()) {
		y = boundary.getCorner().getY() + boundary.getVertical() - view.getVertical();
	}
	if (y < boundary.getCorner().getY()) {
		y = boundary.getCorner().getY();
	}
		
	// Set view.
	view.setCorner(Vector(x, y));
}

// Set view to center window on Object.
// Set to NULL to stop following.
// If p_new_view_following not legit, return -1 else return 0.
int df::WorldManager::setViewFollowing(Object* p_new_view_following) {
	// Set to NULL to turn 'off' following.
	if (p_new_view_following == NULL) {
		p_view_following = NULL;
		return 0;
	}

	// Iterate over all objects. Make sure p_new_view_following
	// is one of the Objects, then set found to true.
	bool found = false;
	ObjectListIterator li = ObjectListIterator(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		Object* object = li.currentObject();
		if (li.currentObject() == p_new_view_following) {
			found = true;
		}
	} // End iterate.

	// If found, ajust attribute accordingly and set view position.
	if (found) {
		p_view_following = p_new_view_following;
		setViewPosition(p_view_following->getPosition());
		return 0;
	}

	// If we get here, was not legit. Don't change current view.
	return -1;
}

// Insert Object into world. Return 0 if ok, else -1.
int df::WorldManager::insertObject(Object* p_o) {
	// Check if Object is already in world
	ObjectListIterator li = ObjectListIterator(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getId() == p_o->getId()) {
			LM.writeLog("df::WorldManager::insertObject(): Given object with id: %d was already in world.", p_o->getId());
			return -1;
		}
	}

	LM.writeLog(-1, "df::WorldManager::insertObject(): Adding given object with id: %d to world.", p_o->getId());
	// Try to add Object to world
	return m_updates.insert(p_o);
}

// Remove Object from world. Return 0 if ok, else -1.
int df::WorldManager::removeObject(Object* p_o) {
	LM.writeLog(-1, "df::WorldManager::removeObject(): Removing given object with id: %d from world.", p_o->getId());
	return m_updates.remove(p_o);
}

// Return list of all Objects in world.
df::ObjectList df::WorldManager::getAllObjects() const {
	return m_updates;
}

// Return list of all Objects in world matching type.
df::ObjectList df::WorldManager::objectsOfType(std::string type) const {
	ObjectList objectsOfType = ObjectList();
	ObjectListIterator li = ObjectListIterator(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getType().compare(type) == 0) {
			LM.writeLog(-10, "df::WorldManager::objectsOfType(): Object found of type %s", type.c_str());
			objectsOfType.insert(li.currentObject());
		}
	}
	return objectsOfType;
}

// Update world.
// Delete Objects marked for deletion.
void df::WorldManager::update() {
	LM.writeLog(-10, "df::WorldManager::update(): accelerating each object according to their accelerations");
	// Update object velocity based on their accelerations.

	// Iterate through all objects.
	ObjectListIterator li = ObjectListIterator(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		// Add acceleration to velocity.
		Object* object = li.currentObject();
		object->setVelocity(object->getVelocity() + object->getAcceleration());
	} // End iterate.

	LM.writeLog(-10, "df::WorldManager::update(): moving each object according to their velocities");
	// Update object position based on their velocities.
	
	// Iterate through all objects.
	for (li.first(); !li.isDone(); li.next()) {
		// Add velocity to position.
		Vector new_pos = li.currentObject()->predictPosition();

		// If Object should change position, then move.
		if (!(new_pos == li.currentObject()->getPosition())) {
			moveObject(li.currentObject(), new_pos);
		}
	} // End iterate.

	LM.writeLog(-10, "df::WorldManager::update(): removing %d objects marked for deletion", m_deletions.getCount());
	// Delete all marked objects.
	li = ObjectListIterator(&m_deletions);
	for (li.first(); !li.isDone(); li.next()) {
		delete li.currentObject();
	}
	LM.writeLog(-10, "df::WorldManager::update(): %d objects left in world", m_updates.getCount());
	
	// Clear list for next update phase.
	m_deletions.clear();
}

// Return list of Objects collided with at position 'where'.
// Collision only with solid Objects.
// Does not consider if p_o is solid or not.
df::ObjectList df::WorldManager::getCollisions(Object* p_o, Vector where) const {
	// Make empty list.
	ObjectList collision_list = ObjectList();
		
	// Iterate through all objects
	ObjectListIterator li = ObjectListIterator(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		Object* p_temp_o = li.currentObject();
		if (p_temp_o != p_o) { // Do not consider self
			// Same location and both solid?
			if (boxIntersectsBox(getWorldBox(p_o), getWorldBox(p_temp_o)) &&
				p_temp_o->isSolid()) {
				collision_list.insert(p_temp_o);
			} // No solid collision.
		} // Not self.
	} // End iterate.

	LM.writeLog(-5, "df::WorldManager::getCollisions(): found %d collisions at (%f, %f)", collision_list.getCount(), where.getX(), where.getY());
	return collision_list;
}

// Move Object.
// If collision with solid, send collision events.
// If no collision with solid, move ok else don't move Object.
// If Object is Spectral, move ok.
// Return 0 if move ok, else -1 if collision with solid.
int df::WorldManager::moveObject(Object* p_o, Vector where) {
	if (p_o->isSolid()) { // Need to be solid for collisions.
		// Get collisions.
		ObjectList list = getCollisions(p_o, where);

		if (!list.isEmpty()) {
			bool do_move = true; // Assume can move.
			// Iterate over list.
			ObjectListIterator li = ObjectListIterator(&list);
			for (li.first(); !li.isDone(); li.next()) {
				Object* p_temp_o = li.currentObject();
				// Create collision event.
				EventCollision c(p_o, p_temp_o, where);
				// Send to both objects.
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				// If both HARD, then cannot move.
				if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD) {
					do_move = false; // Can't move.
				}	
			} // End iterate.
			if (!do_move || p_o->dont_move_this_frame) {
				LM.writeLog(-5, "df::WorldManager::moveObject(): Object id: %d blocked by solid object or by setting dontMoveThisFrame", p_o->getId());
				p_o->dont_move_this_frame = false;
				return -1; // Move not allowed.
			}
		} // No collision.
	} // Object not solid.
		
	// If here, no collision between two HARD objects so allow move.
	LM.writeLog(-10, "df::WorldManager::moveObject(): Object id: %d moved successfully", p_o->getId());
	// Do move.
	Box orig_box = getWorldBox(p_o); // original bounding box
	p_o->setPosition(where); // move object
	Box new_box = getWorldBox(p_o); // new bounding box

	// If view is following this object, adjust view.
	if (p_view_following == p_o) {
		setViewPosition(p_o->getPosition());
	}

	// If object moved from inside to outside world, generate
	// "out of bounds" event.
	// Was in bounds and now out of bounds?
	if (boxIntersectsBox(orig_box, boundary) && !boxIntersectsBox(new_box, boundary)) {
		LM.writeLog(-5, "df::WorldManager::moveObject(): Object id: %d moved out of bounds", p_o->getId());
		EventOut ov; // Create "out" event
		p_o->eventHandler(&ov); // Send to Object
	}
		
	// All is well.
	return 0; // Move was ok.
}

// Indicate Object is to be deleted at end of current game loop.
// Return 0 if ok, else -1.
int df::WorldManager::markForDelete(Object* p_o) {
	LM.writeLog(-1, "df::WorldManager::markForDelete(): marking object with id: %d for deletion", p_o->getId());
	// Object might already have been marked, so only add once.
	ObjectListIterator li = ObjectListIterator(&m_deletions);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject() == p_o) { // Object already in list.
			LM.writeLog("df::WorldManager::markForDelete(): Given object with id: %d was already marked for deletion", p_o->getId());
			return 0; // This is still "ok".
		}
	}

	// Object is not in deletions, search updates
	li = ObjectListIterator(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getId() == p_o->getId()) { // Object already in world.
			// Object not in deletions, but is in world, so mark it.
			m_deletions.insert(p_o);
			return 0;
		}
	}

	LM.writeLog("df::WorldManager::markForDelete(): Given object was non-existent so could not be marked for deletion");
	return -1;
}

// Draw all objects.
void df::WorldManager::draw() {
	df::ObjectListIterator li = df::ObjectListIterator(&m_updates); // All game objects.
	// For each altitude from 0 to MAX_ALTITUDE,
	for (int alt = 0; alt <= MAX_ALTITUDE; alt++) {
		// Draw each object at the current altitude.
		LM.writeLog(-10, "df::WorldManager::draw(): drawing objects at altitude %d", alt);
		for (li.first(); !li.isDone(); li.next()) {
			if (li.currentObject()->getAltitude() == alt) {
				// Normal draw.
				Object* p_temp_o = li.currentObject();

				// Bounding box coordinates are relative to Object.
				// so convert to world coordinates.
				Box temp_box = getWorldBox(p_temp_o);
				
				// Only draw if Object would be visible on window (intersects view).
				if (boxIntersectsBox(temp_box, view) || p_temp_o->getDrawWhenOffScreen()) {
					p_temp_o->draw();
				}
			}
		}
	} // Altitude outer loop.
}
