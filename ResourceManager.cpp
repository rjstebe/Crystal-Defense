#include "LogManager.h"
#include "ResourceManager.h"

// Called only by getInstance().
df::ResourceManager::ResourceManager() {}

// Get the one and only instance of the ResourceManager.
df::ResourceManager& df::ResourceManager::getInstance() {
	static df::ResourceManager& instance = *new ResourceManager();
	return instance;
}

// Get ResourceManager ready to manage resources.
int df::ResourceManager::startUp() {
	return SpriteResourceManager::startUp();
}

// Shut down ResourceManager, freeing up any allocated Sprites, and unload any music and sounds.
void df::ResourceManager::shutDown() {
	for (int i = 0; i < sound_count; i++) {
		sound[i].stop();
	}
	for (int i = 0; i < MAX_MUSICS; i++) {
		if (music[i].getLabel() != "") {
			music[i].stop();
			music[i].setLabel("");
		}
	}
	sound_count = 0;
	music_count = 0;
	SpriteResourceManager::shutDown();
}

// Load Sprite from file.
// Assign indicated label to sprite
// Return 0 if ok, else -1.
int df::ResourceManager::loadSprite(std::string filename, std::string label) {
	return SpriteResourceManager::loadSprite(filename, label);
}

// Unload Sprite within indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSprite(std::string label) {
	return SpriteResourceManager::unloadSprite(label);
}

// Find Sprite within indicated label.
// Return pointer to it if found, else NULL.
df::Sprite* df::ResourceManager::getSprite(std::string label) const {
	return SpriteResourceManager::getSprite(label);
}

// Load Sound from file.
// Return 0 if ok, else -1.
int df::ResourceManager::loadSound(std::string filename, std::string label) {
	if (sound_count == MAX_SOUNDS) {
		LM.writeLog("df::ResourceManager::loadSound(): Cannot load sound, at maximum sounds");
		return -1;
	}
		
	if (sound[sound_count].loadSound(filename) == -1) {
		LM.writeLog("df::ResourceManager::loadSound(): Unable to open sound file: %s", filename.c_str());
		return -1;
	}
		
	// All is well.
	sound[sound_count].setLabel(label);
	sound_count++;
	return 0;
}

// Remove Sound with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadSound(std::string label) {
	for (int i = 0; i < sound_count; i++) {
		if (label == sound[i].getLabel()) {
			sound[i].stop();
			// Scoot over remaining sounds.
			for (int j = i; j < sound_count - 1; j++) {
				sound[j] = sound[j + 1];
			}

			sound_count--;
			return 0;
		}
	}
		
	return -1; // Sound not found.
}

// Find Sound with indicated label.
// Return pointer to it if found, else NULL.
df::Sound* df::ResourceManager::getSound(std::string label) {
	for (int i = 0; i < sound_count; i++) {
		if (label == sound[i].getLabel()) {
			return &sound[i];
		}
	}
		
	return NULL; // Sound not found.
}

// Associated file with Music.
// Return 0 if ok, else -1.
int df::ResourceManager::loadMusic(std::string filename, std::string label) {
	if (music_count == MAX_MUSICS) {
		LM.writeLog("df::ResourceManager::loadMusic(): Cannot load music, at maximum musics");
		return -1;
	}

	if (label == "") {
		LM.writeLog("df::ResourceManager::loadMusic(): \"\" is not a valid label for a music resource");
		return -1;
	}

	if (music[music_count].loadMusic(filename) == -1) {
		LM.writeLog("df::ResourceManager::loadMusic(): Unable to open music file: %s", filename.c_str());
		return -1;
	}

	// Put music in first empty index.
	for (int i = 0; i < MAX_MUSICS; i++) {
		if (music[i].getLabel() == "") {
			// All is well.
			music[i].setLabel(label);
			music_count++;
			return 0;
		}
	}
	
	LM.writeLog("df::ResourceManager::loadMusic(): Error: could not find an empty index even though music_count was less than MAX_MUSICS");
	return -1;
}

// Remove label for Music with indicated label.
// Return 0 if ok, else -1.
int df::ResourceManager::unloadMusic(std::string label) {
	if (label == "") {
		LM.writeLog("df::ResourceManager::unloadMusic(): cannot unload music with invalid label \"\"");
		return -1;
	}

	for (int i = 0; i < MAX_MUSICS; i++) {
		if (label == music[i].getLabel()) {
			// Set music slot to empty.
			music[i].stop();
			music[i].setLabel("");
			music_count--;
			return 0;
		}
	}

	return -1; // Music not found.
}

// Find Music with indicated label.
// Return pointer to it if found, else NULL.
df::Music* df::ResourceManager::getMusic(std::string label) {
	if (label == "") {
		LM.writeLog("df::ResourceManager::unloadMusic(): cannot get music with invalid label \"\"");
		return NULL;
	}

	for (int i = 0; i < MAX_MUSICS; i++) {
		if (label == music[i].getLabel()) {
			return &music[i];
		}
	}

	return NULL; // Music not found.
}
