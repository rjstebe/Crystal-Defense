#include "LogManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

// Called only by getInstance().
df::InputManager::InputManager() {}

// Get the one and only instance of the InputManager.
df::InputManager& df::InputManager::getInstance() {
	static df::InputManager& instance = *new InputManager();
	return instance;
}

// Get window ready to capture input.
// Return 0 if ok, else return -1.
int df::InputManager::startUp() {
	// If DisplayManager has not set up window yet, return -1.
	if (!DM.isStarted()) {
		return -1;
	}
		
	DM.getWindow()->setKeyRepeatEnabled(false);
		
	return Manager::startUp();
}

// Revert back to normal window mode.
void df::InputManager::shutDown() {
	DM.getWindow()->setKeyRepeatEnabled(true);
	Manager::shutDown();
}

// Get input from the keyboard and mouse.
// Pass event along to all Objects.
void df::InputManager::getInput() {
	LM.writeLog(-10, "InputManager.getInput(): getting input");
	// Check past window events.
	sf::Event event;
	while (DM.getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			EventKeyboard ek = EventKeyboard();
			ek.setKeyboardAction(KEY_PRESSED);
			Keyboard::Key key_code = SFMLKeyCodeToDFKeyCode(event.key.code);
			ek.setKey(key_code);
			LM.writeLog(-10, "InputManager.getInput(): detected key press with key code: %d", key_code);
			onEvent(&ek);
		}
		else if (event.type == sf::Event::KeyReleased) {
			EventKeyboard ek = EventKeyboard();
			ek.setKeyboardAction(KEY_RELEASED);
			Keyboard::Key key_code = SFMLKeyCodeToDFKeyCode(event.key.code);
			ek.setKey(key_code);
			LM.writeLog(-10, "InputManager.getInput(): detected key release with key code: %d", key_code);
			onEvent(&ek);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			EventMouse em = EventMouse();
			em.setMouseAction(CLICKED);
			Mouse::Button mouse_button = SFMLMouseButtonToDFMouseButton(event.mouseButton.button);
			em.setMouseButton(mouse_button);
			em.setMousePosition(Vector());
			LM.writeLog(-10, "InputManager.getInput(): detected mouse click with button: %d", mouse_button);
			onEvent(&em);
		}
		else if (event.type == sf::Event::MouseMoved) {
			EventMouse em = EventMouse();
			em.setMouseAction(MOVED);
			em.setMouseButton(Mouse::UNDEFINED_MOUSE_BUTTON);
			em.setMousePosition(Vector(event.mouseMove.x, event.mouseMove.y));
			LM.writeLog(-10, "InputManager.getInput(): detected mouse move with position (%d, %d)", event.mouseMove.x, event.mouseMove.y);
			onEvent(&em);
		}
	} // Window events.

	// Check current key press events for each key supported by SFML.
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		// Get current key while iterating through SFML keys.
		sf::Keyboard::Key sfml_key_code = static_cast<sf::Keyboard::Key>(i);
		Keyboard::Key key_code = SFMLKeyCodeToDFKeyCode(sfml_key_code);
		// If key is a key dragonfly recognizes, and key is pressed
		if (key_code != Keyboard::UNDEFINED_KEY && sf::Keyboard::isKeyPressed(sfml_key_code)) {
			EventKeyboard ek = EventKeyboard();
			ek.setKeyboardAction(KEY_DOWN);
			ek.setKey(key_code);
			LM.writeLog(-10, "InputManager.getInput(): detected key down with key code: %d", key_code);
			onEvent(&ek);
		}
	}

	// Check current mouse press events for each button supported by SFML.
	for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
		// Get current button while iterating through SFML buttons.
		sf::Mouse::Button sfml_mouse_button = static_cast<sf::Mouse::Button>(i);
		Mouse::Button mouse_button = SFMLMouseButtonToDFMouseButton(sfml_mouse_button);
		// If button is a button dragonfly recognizes,
		if (mouse_button != Mouse::UNDEFINED_MOUSE_BUTTON && sf::Mouse::isButtonPressed(sfml_mouse_button)) {
			EventMouse em = EventMouse();
			em.setMouseAction(PRESSED);
			em.setMouseButton(mouse_button);
			em.setMousePosition(Vector());
			LM.writeLog(-10, "InputManager.getInput(): detected mouse button pressed: %d", mouse_button);
			onEvent(&em);
		}
	}
}
