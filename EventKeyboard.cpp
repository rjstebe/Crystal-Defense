#include "EventKeyboard.h"

df::EventKeyboard::EventKeyboard() {
	setType(KEYBOARD_EVENT);
}

// Set key in event.
void df::EventKeyboard::setKey(Keyboard::Key new_key) {
	m_key_val = new_key;
}

// Get key from event.
df::Keyboard::Key df::EventKeyboard::getKey() const {
	return m_key_val;
}

// Set keyboard event in action.
void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action) {
	m_keyboard_action = new_action;
}

// Get keyboard event in action.
df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const {
	return m_keyboard_action;
}

// Convert SFML key codes to Dragonfly key codes
df::Keyboard::Key df::SFMLKeyCodeToDFKeyCode(sf::Keyboard::Key sfml_key_event) {
	using namespace df::Keyboard;
	switch (sfml_key_event) {
	case sf::Keyboard::Space:
		return SPACE;
	case sf::Keyboard::Enter:
		return RETURN;
	case sf::Keyboard::Escape:
		return ESCAPE;
	case sf::Keyboard::Tab:
		return TAB;
	case sf::Keyboard::Left:
		return LEFTARROW;
	case sf::Keyboard::Right:
		return RIGHTARROW;
	case sf::Keyboard::Up:
		return UPARROW;
	case sf::Keyboard::Down:
		return DOWNARROW;
	case sf::Keyboard::Pause:
		return PAUSE;
	case sf::Keyboard::Dash:
		return MINUS;
	case sf::Keyboard::Equal:
		return PLUS;
	case sf::Keyboard::Tilde:
		return TILDE;
	case sf::Keyboard::Period:
		return PERIOD;
	case sf::Keyboard::Comma:
		return COMMA;
	case sf::Keyboard::Slash:
		return SLASH;
	case sf::Keyboard::LControl:
		return LEFTCONTROL;
	case sf::Keyboard::RControl:
		return RIGHTCONTROL;
	case sf::Keyboard::LShift:
		return LEFTSHIFT;
	case sf::Keyboard::RShift:
		return RIGHTSHIFT;
	case sf::Keyboard::F1:
		return F1;
	case sf::Keyboard::F2:
		return F2;
	case sf::Keyboard::F3:
		return F3;
	case sf::Keyboard::F4:
		return F4;
	case sf::Keyboard::F5:
		return F5;
	case sf::Keyboard::F6:
		return F6;
	case sf::Keyboard::F7:
		return F7;
	case sf::Keyboard::F8:
		return F8;
	case sf::Keyboard::F9:
		return F9;
	case sf::Keyboard::F10:
		return F10;
	case sf::Keyboard::F11:
		return F11;
	case sf::Keyboard::F12:
		return F12;
	case sf::Keyboard::A:
		return A;
	case sf::Keyboard::B:
		return B;
	case sf::Keyboard::C:
		return C;
	case sf::Keyboard::D:
		return D;
	case sf::Keyboard::E:
		return E;
	case sf::Keyboard::F:
		return F;
	case sf::Keyboard::G:
		return G;
	case sf::Keyboard::H:
		return H;
	case sf::Keyboard::I:
		return I;
	case sf::Keyboard::J:
		return J;
	case sf::Keyboard::K:
		return K;
	case sf::Keyboard::L:
		return L;
	case sf::Keyboard::M:
		return M;
	case sf::Keyboard::N:
		return N;
	case sf::Keyboard::O:
		return O;
	case sf::Keyboard::P:
		return P;
	case sf::Keyboard::Q:
		return Q;
	case sf::Keyboard::R:
		return R;
	case sf::Keyboard::S:
		return S;
	case sf::Keyboard::T:
		return T;
	case sf::Keyboard::U:
		return U;
	case sf::Keyboard::V:
		return V;
	case sf::Keyboard::W:
		return W;
	case sf::Keyboard::X:
		return X;
	case sf::Keyboard::Y:
		return Y;
	case sf::Keyboard::Z:
		return Z;
	case sf::Keyboard::Num1:
		return NUM1;
	case sf::Keyboard::Num2:
		return NUM2;
	case sf::Keyboard::Num3:
		return NUM3;
	case sf::Keyboard::Num4:
		return NUM4;
	case sf::Keyboard::Num5:
		return NUM5;
	case sf::Keyboard::Num6:
		return NUM6;
	case sf::Keyboard::Num7:
		return NUM7;
	case sf::Keyboard::Num8:
		return NUM8;
	case sf::Keyboard::Num9:
		return NUM9;
	case sf::Keyboard::Num0:
		return NUM0;
	default:
		return UNDEFINED_KEY;
	}
}