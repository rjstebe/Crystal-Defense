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
#include "Bullet.h"

Hero::Hero() {
    setType("Hero");
    setSprite("hero");
    // Set location to something
    df::Vector p(1, 1);
    setPosition(p);

    p_reticle = new Aimer;
    p_reticle->draw();
    move_slowdown = 2;
    move_countdown = move_slowdown;
    fire_slowdown = 15;
    fire_countdown = fire_slowdown;
    health_count = 3;
    setSpeed(1);
    setVelocity(df::Vector(0, 0));
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
            setVelocity(df::Vector(getVelocity().getX(), -1));
        else
            setVelocity(df::Vector(getVelocity().getX(), 0));
        break;
    case df::Keyboard::S:    // down
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            setVelocity(df::Vector(getVelocity().getX(), 1));
        else
            setVelocity(df::Vector(getVelocity().getX(), 0));
        break;
    case df::Keyboard::A:    // up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            setVelocity(df::Vector(-1, getVelocity().getY()));
        else
            setVelocity(df::Vector(0, getVelocity().getY()));
        break;
    case df::Keyboard::D:    // up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
            setVelocity(df::Vector(1, getVelocity().getY()));
        else
            setVelocity(df::Vector(0, getVelocity().getY()));
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

    // Move countdown.
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;
    fire_countdown--;
    if (fire_countdown < 0)
        fire_countdown = 0;
}

void Hero::fire(df::Vector target) {
    if (fire_countdown > 0)
        return;
    fire_countdown = fire_slowdown;
    df::Vector v = target - getPosition();
    v.normalize();
    v.scale(1);
    Bullet* p = new Bullet(getPosition());
    p->setVelocity(v);
    // Play "fire" sound.
    //df::Sound* p_sound = RM.getSound("fire");
    //p_sound->play();
}

void Hero::mouse(const df::EventMouse* p_mouse_event) {

    p_reticle->draw();
    if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
        (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
        fire(pixelsToSpaces(p_reticle->getPosition()));
    }
        
}

void Hero::hit() {
        
    
}
