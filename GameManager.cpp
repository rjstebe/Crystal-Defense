#include <chrono>
#include <thread>

#include "LogManager.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Clock.h"
#include "EventStep.h"

// Called only by getInstance().
df::GameManager::GameManager() {}

// Get the singleton instance of the GameManager.
df::GameManager& df::GameManager::getInstance() {
	static df::GameManager& instance = *new GameManager();
	return instance;
}

// Start up all GameManager services.
int df::GameManager::startUp() {
	if (LM.startUp()) {
		return -1;
	}
	if (DM.startUp()) {
		return -1;
	}
	if (RM.startUp()) {
		return -1;
	}
	IM.startUp();
	WM.startUp();
	setType("GameManager");
	return df::Manager::startUp();
}

// Shut down GameManager services.
void df::GameManager::shutDown() {
	df::Manager::shutDown();
	game_over = false;
	frame_time = FRAME_TIME_DEFAULT;
	game_loop_count = 0;
	WM.shutDown();
	IM.shutDown();
	RM.shutDown();
	DM.shutDown();
	LM.shutDown();
}

// Run game loop.
void df::GameManager::run() {
	using namespace std::chrono;
	using namespace std::this_thread;
	long int loop_time, intended_sleep_time, adjust_time = 0;
	df::Clock clock;
	LM.writeLog("df::GameManager::run(): game loop started running");

	// Run game loop until game_over is set to true.
	while (!game_over) {
		// Reset clock.
		clock.delta();
		LM.writeLog(-10, "df::GameManager::run(): game loop %d started", game_loop_count);

		// Perform main game loop functions.
		// Get input, e.g., keyboard/mouse.
		IM.getInput();
		// Provide step event to all objects.
		EventStep s = EventStep(game_loop_count);
		onEvent(&s);
		// Update game world state.
		// Delete objects marked for deletion.
		WM.update();
		// Draw current scene to back buffer.
		WM.draw();
		// Swap back buffer to current buffer.
		DM.swapBuffers();
		// Increment game loop count.
		game_loop_count++;

		// Sleep for rest of frame.
		loop_time = clock.split();
		intended_sleep_time = frame_time - loop_time - adjust_time; // in microseconds
		clock.delta();
		if (intended_sleep_time > 0) {
			sleep_for(microseconds(intended_sleep_time));
		}

		// Set adjust_time equal to the excess sleeping that occurred.
		adjust_time = clock.split() - intended_sleep_time;
		if (adjust_time < 0) {
			adjust_time = 0;
		}
	}
}

// Set game over status to indicated value.
// If true (default), will stop game loop.
void df::GameManager::setGameOver(bool new_game_over) {
	game_over = new_game_over;
}

// Get game over status.
bool df::GameManager::getGameOver() const {
	return game_over;
}

// Set the frame time. (returns -1 and fails if GameManager is running).
int df::GameManager::setFrameTime(int new_frame_time) {
	if (isStarted()) {
		return -1;
	}
	frame_time = new_frame_time;
	return 0;
}

// Return frame time.
// Frame time is target time for game loop, in milliseconds.
int df::GameManager::getFrameTime() const {
	return frame_time;
}

// Return current game loop count.
int df::GameManager::getGameLoopCount() const {
	return game_loop_count;
}
