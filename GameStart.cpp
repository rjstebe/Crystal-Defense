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
#include "EventCrystalDeath.h"

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
    initialized = 0;



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
            if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
                if (started) {
                    GameDone();
                    lifted = 0;
                }
                else {
                    if (lifted) {
                        GM.setGameOver();
                    }
                }
            }
            else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
                lifted = 1;
            }
            break;
        default: // Key is not handled.
            break;
        }
        return 1;
    }
    if (p_e->getType() == CRYSTAL_DEATH_EVENT) {
        GameDone();
    }
    // If get here, have ignored this event.
    return 0;
}

void GameStart::GameDone()
{
    this->setLocation(df::CENTER_CENTER);
    LM.writeLog("Crystal down");
    df::ObjectList obj = WM.getAllObjects();
    
    df::ObjectListIterator li = df::ObjectListIterator(&obj);
    for (li.first(); !li.isDone() ; li.next()) {
        if (li.currentObject()->getType() == "GameStart") {
            LM.writeLog("only once");
        }
        else if (li.currentObject()->getType() == "Room") {
            LM.writeLog("room not deleted");
        }
        else if (li.currentObject()->getType() == "EnemyManager") {
            LM.writeLog("manager not deleted");
        }
        else {
            WM.markForDelete(li.currentObject());
        }

    }
    started = 0;
    WM.setViewFollowing(this);
    EM.shutDown();
    LM.writeLog("game done");
}

void GameStart::start() {
    LM.writeLog("Start called");
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
    WM.setBoundary(df::Box(df::Vector(-100, -100), 200, 200));
    WM.setViewFollowing(p_hero);
    
    EM.startUp();
    LM.writeLog("EM started");
    if (!initialized) {
        Room* a = EM.addRoom('a', df::Box(df::Vector(25, -5), 30, 30), false);
        Room* b = EM.addRoom('b', df::Box(df::Vector(0, 0), 20, 20), true);
        Room* c = EM.addRoom('c', df::Box(df::Vector(30, -30), 20, 20), true);
        Room* d = EM.addRoom('d', df::Box(df::Vector(60, 0), 20, 20), true);
        Room* e = EM.addRoom('e', df::Box(df::Vector(30, 30), 20, 20), true);
        LM.writeLog("Rooms added");
        a->addRoute('b', df::Vector(25, 10));
        a->addRoute('c', df::Vector(40, -5));
        a->addRoute('d', df::Vector(55, 10));
        a->addRoute('e', df::Vector(40, 25));
        b->addRoute('a', df::Vector(20, 10));
        c->addRoute('a', df::Vector(40, -10));
        d->addRoute('a', df::Vector(60, 10));
        e->addRoute('a', df::Vector(40, 30));
        LM.writeLog("routes added");
        initialized = 1;
    }


    started = 1;
    this->setPosition(df::Vector(-100, -100));
    LM.writeLog("start complete");
    // Pause start music.
    //p_music->pause();
}

int GameStart::draw() {
    return df::Object::draw();
}

//void GameStart::playMusic() {
//    p_music->play();
//}