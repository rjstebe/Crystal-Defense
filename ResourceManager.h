#pragma once

// System includes.
#include <string>

// Engine includes.
#include "Manager.h"
#include "SpriteResourceManager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

namespace df {

const int MAX_SOUNDS = 128;
const int MAX_MUSICS = 128;

#define RM df::ResourceManager::getInstance() // Two-letter acronym.

class ResourceManager : public SpriteResourceManager {
private:
	ResourceManager();                       // Private (a singleton).
	ResourceManager(ResourceManager const&); // Don't allow copy.
	void operator=(ResourceManager const&);  // Don't allow assignment.
	df::Sound sound[MAX_SOUNDS]; // Array of sound buffers.
	int sound_count = 0;         // Count of number of loaded sounds.
	df::Music music[MAX_MUSICS]; // Array of music buffers.
	int music_count = 0;         // Count of number of loaded musics.

public:
	// Get the one and only instance of the ResourceManager.
	static ResourceManager& getInstance();
	
	// Get ResourceManager ready to manage resources.
	int startUp();
	
	// Shut down ResourceManager, freeing up any allocated Sprites.
	void shutDown();
	
	// Load Sprite from file.
	// Assign indicated label to sprite
	// Return 0 if ok, else -1.
	int loadSprite(std::string filename, std::string label);
	
	// Unload Sprite within indicated label.
	// Return 0 if ok, else -1.
	int unloadSprite(std::string label);
	
	// Find Sprite within indicated label.
	// Return pointer to it if found, else NULL.
	Sprite* getSprite(std::string label) const;

	// Load Sound from file.
	// Return 0 if ok, else -1.
	int loadSound(std::string filename, std::string label);
	
	// Remove Sound with indicated label.
	// Return 0 if ok, else -1.
	int unloadSound(std::string label);
	
	// Find Sound with indicated label.
	// Return pointer to it if found, else NULL.
	Sound* getSound(std::string label);
	
	// Associated file with Music.
	// Return 0 if ok, else -1.
	int loadMusic(std::string filename, std::string label);
	
	// Remove label for Music with indicated label.
	// Return 0 if ok, else -1.
	int unloadMusic(std::string label);
	
	// Find Music with indicated label.
	// Return pointer to it if found, else NULL.
	Music* getMusic(std::string label);
};

}
