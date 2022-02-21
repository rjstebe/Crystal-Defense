#pragma once

// System includes.
#include <SFML/Graphics.hpp>

// Engine includes.
#include "Color.h"
#include "Manager.h"
#include "Vector.h"

namespace df {

// Defaults for SFML window .
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";

enum Justification {
	LEFT_JUSTIFIED,
	CENTER_JUSTIFIED,
	RIGHT_JUSTIFIED,
};

#define DM df::DisplayManager::getInstance() // Two-letter acronym.

class DisplayManager : public Manager {
	
private:
	DisplayManager();                      // Private (a singleton).
	DisplayManager(DisplayManager const&); // Don't allow copy.
	void operator=(DisplayManager const&); // Don't allow assignment.
	sf::Font m_font = sf::Font();                                          // Font used for ASCII graphics.
	sf::RenderWindow* m_p_window = NULL;                                   // Pointer to SFML window.
	int m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;     // Horizontal pixels in window.
	int m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;         // Vertical pixels in window.
	int m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;       // Horizontal ASCII spaces in window.
	int m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;           // Vertical ASCII spaces in window.
	sf::Color m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT; // Background window color.
	
public:
	// Get the one and only instance of the DisplayManager.
	static DisplayManager& getInstance();
	
	// Open graphics window, ready for text-based display.
	// Return 0 if ok, else -1.
	int startUp();
	
	// Close graphics window.
	void shutDown();
	
	// Draw character at window location (x, y) with color.
	// Return 0 if ok, else -1.
	int drawCh(Vector world_pos, char ch, Color color) const;

	// Draw string at window location (x, y) with default color.
	// Justified left, center or right.
	// Return 0 if ok, else -1.
	int drawString(Vector pos, std::string str, Justification just, Color color) const;
	
	// Return window's horizontal maximum (in characters).
	int getHorizontal() const;
	
	// Return window's vertical maximum (in characters).
	int getVertical() const;
	
	// Return window's horizontal maximum (in pixels).
	int getHorizontalPixels() const;
	
	// Return window's vertical maximum (in pixels).
	int getVerticalPixels() const;

	// Set default background color. Return true if ok, else false.
	bool setBackgroundColor(Color new_color);
	
	// Render current window buffer.
	// Return 0 if ok, else -1.
	int swapBuffers();
	
	// Return pointer to SFML graphics window.
	sf::RenderWindow* getWindow() const;
};

// Compute character height, based on window size and font.
float charHeight();

// Compute character width, based on window size and font.
float charWidth();

// Convert ASCII space (x, y) to window pixels (x, y).
Vector spacesToPixels(Vector spaces);

// Convert window pixels (x, y) to ASCII spaces (x, y).
Vector pixelsToSpaces(Vector pixels);

// Convert dragonfly Color to SFML Color.
sf::Color DFColorToSFMLColor(Color color);

};
