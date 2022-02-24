#include "utility.h"
#include "DisplayManager.h"
#include "LogManager.h"

// Private (a singleton).
df::DisplayManager::DisplayManager() {}

// Get the one and only instance of the DisplayManager.
df::DisplayManager& df::DisplayManager::getInstance() {
	static df::DisplayManager& instance = *new DisplayManager();
	return instance;
}

// Open graphics window, ready for text-based display.
// Return 0 if ok, else -1.
int df::DisplayManager::startUp() {
	// If window already created, just invoke Manager startup.
	if (m_p_window != NULL) {
		return df::Manager::startUp();
	}
	
	// an sf::RenderWindow for drawing.
	sf::VideoMode* p_video_mode = new sf::VideoMode(df::WINDOW_HORIZONTAL_PIXELS_DEFAULT, df::WINDOW_VERTICAL_PIXELS_DEFAULT);
	m_p_window = new sf::RenderWindow(*p_video_mode, df::WINDOW_TITLE_DEFAULT, df::WINDOW_STYLE_DEFAULT);

	// Turn off mouse cursor for window.
	m_p_window->setMouseCursorVisible(false);
		
	// Synchronize refresh rate with monitor.
	m_p_window->setVerticalSyncEnabled(true);
	
	// Load font.
	m_font = sf::Font();
	if (m_font.loadFromFile(FONT_FILE_DEFAULT) == false) {
		LM.writeLog("Error! Unable to loadd font \"%s\".", FONT_FILE_DEFAULT);
		return -1;
	}

	return df::Manager::startUp();
}

// Close graphics window.
void df::DisplayManager::shutDown() {
	df::Manager::shutDown();
	m_window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
}

// Draw character at window location (x, y) with color.
// Return 0 if ok, else -1.
int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {
	// Make sure window is allocated.
	if (m_p_window == NULL) {
		return -1;
	}

	// Convert world position in spaces (x, y) to view position in pixels (x, y).
	Vector pixel_pos = spacesToPixels(worldToView(world_pos));
		
	// Draw background rectangle since text is "see-through" in SFML.
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(m_window_background_color);
	rectangle.setPosition(pixel_pos.getX(), pixel_pos.getY());
	m_p_window->draw(rectangle);
		
	// Create character text to draw.
	static sf::Text text(" ", m_font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold); // Make bold, since looks better.
	text.setScale(sf::Vector2f(1.8, 1));
		
	// Scale to right size.
	if (charWidth() < charHeight()) {
		text.setCharacterSize(charWidth() * 2);
	}
	else {
		text.setCharacterSize(charWidth());
	}
		
	// Set SFML color based on Dragonfly color.
	text.setFillColor(df::DFColorToSFMLColor(color));

	// Set position in window (in pixels).
	text.setPosition(pixel_pos.getX() + charWidth() / 10, pixel_pos.getY() - charHeight() / 5);
		
	// Draw character.
	m_p_window->draw(text);

	return 0;
}

// Draw string at window location (x, y) with default color.
// Justified left, center or right.
// Return 0 if ok, else -1.
int df::DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const {
	// Get starting position.
	Vector starting_pos = pos;
	switch (just) {
	case CENTER_JUSTIFIED:
		starting_pos.setX(pos.getX() - (float)str.size() / 2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size());
		break;
	case LEFT_JUSTIFIED:
	default:
		break;
	}
		
	// Draw string character by character.
	for (int i = 0; i < str.size(); i++) {
		Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}
		
	// All is well.
	return 0;
}

// Return window's horizontal maximum (in characters).
int df::DisplayManager::getHorizontal() const {
	return m_window_horizontal_chars;
}

// Return window's vertical maximum (in characters).
int df::DisplayManager::getVertical() const {
	return m_window_vertical_chars;
}

// Return window's horizontal maximum (in pixels).
int df::DisplayManager::getHorizontalPixels() const {
	return m_window_horizontal_pixels;
}

// Return window's vertical maximum (in pixels).
int df::DisplayManager::getVerticalPixels() const {
	return m_window_vertical_pixels;
}

// Set default background color. Return true if ok, else false.
bool df::DisplayManager::setBackgroundColor(Color new_color) {
	if (new_color == UNDEFINED_COLOR) {
		return false;
	}
	m_window_background_color = DFColorToSFMLColor(new_color);
	return true;
}

// Render current window buffer.
// Return 0 if ok, else -1.
int df::DisplayManager::swapBuffers() {
	// Make sure window is allocated.
	if (m_p_window == NULL) {
		return -1;
	}
		
	// Display current window;
	m_p_window->display();
		
	// Clear other window to get ready for next draw.
	m_p_window->clear(m_window_background_color);
		
	return 0; // Success.
}

// Return pointer to SFML graphics window.
sf::RenderWindow* df::DisplayManager::getWindow() const {
	return m_p_window;
}

// Compute character height, based on window size and font.
float df::charHeight() {
	return (float)DM.getVerticalPixels() / DM.getVertical();
}

// Compute character width, based on window size and font.
float df::charWidth() {
	return (float)DM.getHorizontalPixels() / DM.getHorizontal();
}

// Convert ASCII space (x, y) to window pixels (x, y).
df::Vector df::spacesToPixels(df::Vector spaces) {
	return df::Vector(spaces.getX() * df::charWidth(), spaces.getY() * df::charHeight());
}

// Convert window pixels (x, y) to ASCII spaces (x, y).
df::Vector df::pixelsToSpaces(df::Vector pixels) {
	return df::Vector(pixels.getX() / df::charWidth(), pixels.getY() / df::charHeight());
}

// Convert dragonfly Color to SFML Color.
sf::Color df::DFColorToSFMLColor(df::Color color) {
	switch (color) {
	case BLACK:
		return sf::Color::Black;
	case RED:
		return sf::Color::Red;
	case GREEN:
		return sf::Color::Green;
	case YELLOW:
		return sf::Color::Yellow;
	case BLUE:
		return sf::Color::Blue;
	case MAGENTA:
		return sf::Color::Magenta;
	case CYAN:
		return sf::Color::Cyan;
	case WHITE:
		return sf::Color::White;
	default:
		return sf::Color::Transparent;
	}
}