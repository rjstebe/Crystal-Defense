#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Aimer.h"

class Hero : public df::Object {
private:
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(int dx, int dy);
	int x_dir;
	int y_dir;
	int move_slowdown;
	int move_countdown;
	int fire_slowdown;
	int fire_countdown;
	int health_count;
	void step();
	void fire(df::Vector target);
	void mouse(const df::EventMouse* p_mouse_event);
	Aimer* p_reticle;

public:
	Hero();
	~Hero();
	int eventHandler(const df::Event* p_e) override;
	void hit();
};