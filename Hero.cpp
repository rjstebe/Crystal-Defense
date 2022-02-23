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

    p_reticle = new Reticle;
    p_reticle->draw();
    move_slowdown = 2;
    move_countdown = move_slowdown;
    fire_slowdown = 15;
    fire_countdown = fire_slowdown;
    health_count = PLAYER_HEALTH;
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

void Hero::hit(const df::EventCollision* p_collision_event) {
    df::Object* other;
    if (p_collision_event->getObject1()->getType() == "Hero") {
        other = p_collision_event->getObject2();
    }
    else {
        other = p_collision_event->getObject1();
    }
    
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
