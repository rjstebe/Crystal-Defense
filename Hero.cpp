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
#include "utility.h"

// Game includes.
#include "EnemyManager.h"
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
    return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::W:    // up
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            input = input + df::Vector(0, -move_speed);
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            input = input + df::Vector(0, move_speed);
        break;
    case df::Keyboard::S:    // down
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            input = input + df::Vector(0, move_speed);
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            input = input + df::Vector(0, -move_speed);
        break;
    case df::Keyboard::A:    // left
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            input = input + df::Vector(-move_speed, 0);
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            input = input + df::Vector(move_speed, 0);
        break;
    case df::Keyboard::D:    // right
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            input = input + df::Vector(move_speed, 0);
        else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            input = input + df::Vector(-move_speed, 0);
        break;
    }
}

void Hero::step() {
    LM.writeLog("Hero::step(): position: (%f, %f)", getPosition().getX(), getPosition().getY());
    if (alive) {
        handleMove(input);
        // Fire countdown.
        fire_countdown--;
        if (fire_countdown < 0)
            fire_countdown = 0;
    }
    else {
        respawn_timer--;
        if (respawn_timer <= 0) {
            LM.writeLog(0, "Hero::step(): Hero respawned with max health: %d", max_health);
            alive = true;
            fire_countdown = fire_slowdown;
            health = max_health;
            df::EventView ev("health", max_health, false);
            WM.onEvent(&ev);
        }
    }
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
        (p_mouse_event->getMouseButton() == df::Mouse::LEFT) &&
        alive) {
        fire(WM.getView().getCorner() + pixelsToSpaces(p_reticle->getPosition()));
    }
}

int Hero::handleMove(df::Vector move)
{
    df::ObjectList walls = WM.objectsOfType("Wall");
    bool x_blocked = false;
    bool y_blocked = false;
    df::Box cur = df::getWorldBox(this);
    df::Box next = cur;
    next.setCorner(cur.getCorner() + input);
    df::ObjectListIterator li = df::ObjectListIterator(&walls);
    for (li.first(); !li.isDone() && !(x_blocked && y_blocked); li.next()) {
        df::Box wall = df::getWorldBox(li.currentObject());
        if (df::boxIntersectsBox(next, wall)) {
            if (cur.getCorner().getX() > wall.getCorner().getX() + wall.getHorizontal() ||
                cur.getCorner().getX() + cur.getHorizontal() < wall.getCorner().getX()) {
                x_blocked = true;
            }
            if (cur.getCorner().getY() > wall.getCorner().getY() + wall.getVertical() ||
                cur.getCorner().getY() + cur.getVertical() < wall.getCorner().getY()) {
                y_blocked = true;
            }
        }
    }
    LM.writeLog(-10, "Hero::handleMove(): x_blocked: %d, y_blocked: %d", x_blocked, y_blocked);
    setVelocity(input);
    if (x_blocked) {
        setVelocity(df::Vector(0, getVelocity().getY()));
    }
    if (y_blocked) {
        setVelocity(df::Vector(getVelocity().getX(), 0));
    }
    return 0;
}

// When damaged, update health and corresponding UI elements.
void Hero::damaged(const EventDamage* p_ed) {
    if (alive) {
        LM.writeLog(-5, "Hero::damaged(): received damage event: damage: %d", p_ed->getDamage());
        health -= p_ed->getDamage();
        // Send view event to view.
        df::EventView ev("health", -p_ed->getDamage(), true);
        WM.onEvent(&ev);
        if (health <= 0) {
            LM.writeLog(0, "Hero::step(): Hero died with health: %d, respawning in %d frames", health, respawn_time);
            health = 0;
            df::EventView ev("health", 0, false);
            WM.onEvent(&ev);
            alive = false;
            setPosition(EM.getCrystal()->getPosition());
            setVelocity(df::Vector());
            respawn_timer = respawn_time;
            WM.setViewPosition(getPosition());
            LM.writeLog(0, "Hero::step(): set position to (%f, %f)", EM.getCrystal()->getPosition().getX(), EM.getCrystal()->getPosition().getY());
            LM.writeLog(0, "Hero::step(): new velocity: (%f, %f)", getVelocity().getX(), getVelocity().getY());
            LM.writeLog(0, "Hero::step(): new position: (%f, %f)", getPosition().getX(), getPosition().getY());
        }
    }
}

// Upgrades the players fire rate by reducing the slowdown.
int Hero::firerateUpgrade() {
    fire_slowdown *= 0.75;
    return fire_slowdown;
}

int Hero::healthUpgrade() {
    max_health += 2;
    df::EventView ev("health", 2, true);
    WM.onEvent(&ev);
    return max_health;
}
