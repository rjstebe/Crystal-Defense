#include "Hero.h"

// Engine includes.
#include "LogManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventView.h"
#include "EventMouse.h"
#include "EventCollision.h"

// Game includes.
#include "EventDamage.h"
#include "Bullet.h"
Hero::Hero() {
    setType("Hero");
    setSprite("hero");
    // Set location to something
    df::Vector p(20, 10);
    setPosition(p);
    setSolidness(df::SOFT);
    setAltitude(3);

    // Set up player health UI element
    df::ViewObject* player_health = new df::ViewObject();
    player_health->setColor(df::RED);
    player_health->setLocation(df::TOP_CENTER);
    player_health->setViewString("health");
    player_health->setValue(PLAYER_HEALTH);
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
        step();
        return 1;
    }
    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        mouse(p_mouse_event);
        return 1;
    }
    if (p_e->getType() == DAMAGE_EVENT) {
        const EventDamage* p_ed = dynamic_cast<const EventDamage*>(p_e);
        damaged(p_ed);
        return 1;
    }
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event =
            dynamic_cast <const df::EventCollision*> (p_e);
        hit(p_collision_event);
        return 1;
    }
    return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
    df::Vector v = getVelocity();
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::W:    // up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            setVelocity(df::Vector(v.getX(), v.getY() - move_speed));
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            setVelocity(df::Vector(v.getX(), v.getY() + move_speed));
        break;
    case df::Keyboard::S:    // down
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            setVelocity(df::Vector(v.getX(), v.getY() + move_speed));
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            setVelocity(df::Vector(v.getX(), v.getY() - move_speed));
        break;
    case df::Keyboard::A:    // left
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            setVelocity(df::Vector(v.getX() - move_speed, v.getY()));
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            setVelocity(df::Vector(v.getX() + move_speed, v.getY()));
        break;
    case df::Keyboard::D:    // right
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            setVelocity(df::Vector(v.getX() + move_speed, v.getY()));
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            setVelocity(df::Vector(v.getX() - move_speed, v.getY()));
        break;
    }
}

void Hero::step() {
    // Fire countdown.
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
    if ((p_mouse_event->getMouseAction() == df::PRESSED) &&
        (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
        fire(WM.getView().getCorner() + pixelsToSpaces(p_reticle->getPosition()));
    }
}

void Hero::hit(const df::EventCollision* p_collision_event) {
    
}

// When damaged, update health and corresponding UI elements.
void Hero::damaged(const EventDamage* p_ed) {
    LM.writeLog(-5, "Crystal::eventHandler(): received damage event: damage: %d", p_ed->getDamage());
    health_count -= p_ed->getDamage();
    // Send view event to view.
    df::EventView ev("health", -p_ed->getDamage(), true);
    WM.onEvent(&ev);
}

// Upgrades the players fire rate by reducing the slowdown.
int Hero::firerateUpgrade() {
    fire_slowdown *= 0.75;
    return fire_slowdown;
}
