#pragma once

#include "Manager.h"

namespace df {

// Default frame time (game loop time) in milliseconds (33,333 us == 30 fps).
const int FRAME_TIME_DEFAULT = 33333;

#define GM df::GameManager::getInstance() // Two-letter acronym.

class GameManager : public Manager {
private:
	GameManager();                       // Private since a singleton.
	GameManager(GameManager const&);     // Don't allow copy.
	void operator=(GameManager const&);  // Don't allow assignment.
	bool game_over = false;              // True, then game loop should stop.
	int frame_time = FRAME_TIME_DEFAULT; // Target time per game loop, in milliseconds.
	int game_loop_count = 0;             // Number of game loops completed.

public:
	// Get the singleton instance of the GameManager.
	static GameManager& getInstance();

	// Start up all GameManager services.
	int startUp();

	// Shut down GameManager services.
	void shutDown();

	// Run game loop.
	void run();

	// Set game over status to indicated value.
	// If true (default), will stop game loop.
	void setGameOver(bool new_game_over=true);

	// Get game over status.
	bool getGameOver() const;

	// Set the frame time. (returns -1 and fails if GameManager is running).
	int setFrameTime(int frame_time);

	// Return frame time.
	// Frame time is target time for game loop, in milliseconds.
	int getFrameTime() const;

	// Return current game loop count.
	int getGameLoopCount() const;
};

}


