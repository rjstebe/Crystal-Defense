#include "Hero.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventView.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "Aimer.h"

Hero::Hero() {
    setType("Hero");
    setSprite("hero");
    // Set location to something
    df::Vector p(1, 1);
    setPosition(p);
    x_dir = 0;
    y_dir = 0;
    p_reticle = new Aimer;
    p_reticle->draw();
    move_slowdown = 2;
    move_countdown = move_slowdown;
    fire_slowdown = 15;
    fire_countdown = fire_slowdown;
    health_count = 3;
}

Hero::~Hero() {
}

int Hero::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event =
            dynamic_cast <const df::EventKeyboard*> (p_e);
        kbd(p_keyboard_event);
        return 1;
    }

    if (p_e->getType() == df::STEP_EVENT) {
        p_reticle->draw();
        step();
        return 1;
    }
    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        mouse(p_mouse_event);
        return 1;
    }
    return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
// ADD MORE SWITCH CASES
    switch (p_keyboard_event->getKey()) {

    case df::Keyboard::Q:			// quit
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
            WM.markForDelete(this);
        }
        break;
    case df::Keyboard::W:    // up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            y_dir = -1;
        else
            y_dir = 0;
        break;
    case df::Keyboard::S:    // down
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            y_dir = 1;
        else
            y_dir = 0;
        break;
    case df::Keyboard::A:    // up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            x_dir = -1;
        else
            x_dir = 0;
        break;
    case df::Keyboard::D:    // up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            x_dir = 1;
        else
            x_dir = 0;
        break;

    }
}

void Hero::move(int dx, int dy) {
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;
    df::Vector new_pos(getPosition().getX()+dx, getPosition().getY() + dy);
    WM.moveObject(this, new_pos);
}

void Hero::step() {
    move(x_dir, y_dir);
    // Move countdown.
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;
    fire_countdown--;
    if (fire_countdown < 0)
        fire_countdown = 0;
}

void Hero::fire(df::Vector target) {

}

void Hero::mouse(const df::EventMouse* p_mouse_event) {
    LM.writeLog("Hero mouse event, %d %d", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY());
    p_reticle->draw();
    if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
        (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
        fire(p_mouse_event->getMousePosition());
}

void Hero::hit() {

}
