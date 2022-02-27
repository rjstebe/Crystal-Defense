#include "GameStart.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Hero.h"
#include "Crystal.h"
#include "Room.h"
#include "EnemyManager.h"
#include "HealthPowerUp.h"
#include "FireratePowerUp.h"
#include "Bullet.h"
#include "Wall.h"
#include "WorldManager.h"
#include "LogManager.h"

GameStart::GameStart() {

    setType("GameStart");
    setSprite("gamestart");
    // Put in center of window.
    setLocation(df::CENTER_CENTER);
    LM.writeLog("Started");
    // Play start music.
    //p_music = RM.getMusic("start music");
    //playMusic();
    started = 0;



}

int GameStart::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play
            if (!started) {
                start();
                started = 1;
            }
            break;
        case df::Keyboard::Q:			// quit
            GM.setGameOver();
            break;
        default: // Key is not handled.
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start() {
    Hero* p_hero = new Hero();
    new Crystal;
    new Enemy(df::Vector(1, 10));
    new Enemy(df::Vector(40, -15));
    new HealthPowerUp;
    new FireratePowerUp;
    new Bullet(df::Vector(0, 0));
    new Wall(df::Vector(5, 5), df::Vector(10, 5));
    new Wall(df::Vector(25, 5), df::Vector(15, 5));
    new Wall(df::Vector(5, 5), df::Vector(5, 15));
    WM.setViewFollowing(p_hero);
    WM.setBoundary(df::Box(df::Vector(-100, -100), 200, 200));
    
    EM.startUp();
    Room* a = EM.addRoom('a', df::Box(df::Vector(25, -5), 30, 30), false);
    Room* b = EM.addRoom('b', df::Box(df::Vector(0, 0), 20, 20), true);
    Room* c = EM.addRoom('c', df::Box(df::Vector(30, -30), 20, 20), true);
    Room* d = EM.addRoom('d', df::Box(df::Vector(60, 0), 20, 20), true);
    Room* e = EM.addRoom('e', df::Box(df::Vector(30, 30), 20, 20), true);
    a->addRoute('b', df::Vector(25, 10));
    a->addRoute('c', df::Vector(40, -5));
    a->addRoute('d', df::Vector(55, 10));
    a->addRoute('e', df::Vector(40, 25));
    b->addRoute('a', df::Vector(20, 10));
    c->addRoute('a', df::Vector(40, -10));
    d->addRoute('a', df::Vector(60, 10));
    e->addRoute('a', df::Vector(40, 30));

    LM.writeLog("start called");
    this->setPosition(df::Vector(-100, -100));

    // Pause start music.
    //p_music->pause();
}

int GameStart::draw() {
    return df::Object::draw();
}

//void GameStart::playMusic() {
//    p_music->play();
//}