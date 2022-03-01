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
    df::ObjectList obj = WM.getAllObjects();
    
    df::ObjectListIterator li = df::ObjectListIterator(&obj);
    for (li.first(); !li.isDone() ; li.next()) {
        if (li.currentObject()->getType() == "GameStart") {
            
        }
        else if (li.currentObject()->getType() == "Room") {
            
        }
        else if (li.currentObject()->getType() == "EnemyManager") {
            
        }
        else {
            WM.markForDelete(li.currentObject());
        }

    }
    started = 0;
    this->setLocation(df::CENTER_CENTER);
    WM.setViewFollowing(this);
    EM.shutDown();
}

void GameStart::start() {
    new FireratePowerUp(df::Vector(5, 5));
    new HealthPowerUp(df::Vector(8, 8));
    Hero* p_hero = new Hero(df::Vector(2, 2));
    new Crystal(df::Vector(2, 2));
    setWalls();
    WM.setBoundary(df::Box(df::Vector(-100, -100), 200, 200));
    WM.setViewFollowing(p_hero);
    
    EM.startUp();
    if (!initialized) {
        initialized = 1;
        Room* a = EM.addRoom('a', df::Box(df::Vector(-10, -10), 24, 24), false);
        Room* b = EM.addRoom('b', df::Box(df::Vector(-25, -5), 9, 19), false);
        Room* c = EM.addRoom('c', df::Box(df::Vector(-5, -40), 14, 24), false);
        Room* d = EM.addRoom('d', df::Box(df::Vector(20, -5), 14, 19), false);
        Room* e = EM.addRoom('e', df::Box(df::Vector(-5, 20), 14, 14), false);
        Room* f = EM.addRoom('f', df::Box(df::Vector(-45, 0), 14, 34), true);
        Room* g = EM.addRoom('g', df::Box(df::Vector(-30, -40), 19, 14), true);
        Room* i = EM.addRoom('i', df::Box(df::Vector(15, -35), 19, 19), true);
        Room* j = EM.addRoom('j', df::Box(df::Vector(40, -30), 19, 54), true);
        Room* k = EM.addRoom('k', df::Box(df::Vector(-40, 40), 69, 14), true);
        Room* l = EM.addRoom('l', df::Box(df::Vector(-25, 20), 14, 9), true);
        a->addRoute('b', df::Vector(-10, 2));
        a->addRoute('c', df::Vector(2, -10));
        a->addRoute('d', df::Vector(14, 2));
        a->addRoute('e', df::Vector(2, 14));
        a->addRoute('f', df::Vector(-25, 7));
        a->addRoute('g', df::Vector(-5, -33));
        a->addRoute('i', df::Vector(9, -23));
        a->addRoute('j', df::Vector(34, 7));
        a->addRoute('k', df::Vector(7, 34));
        a->addRoute('l', df::Vector(-5, 27));
        b->addRoute('a', df::Vector(-16, 2));
        c->addRoute('a', df::Vector(2, -16));
        d->addRoute('a', df::Vector(20, 2));
        e->addRoute('a', df::Vector(2, 20));
        f->addRoute('a', df::Vector(-31, 7));
        g->addRoute('a', df::Vector(-11, -33));
        i->addRoute('a', df::Vector(15, -23));
        j->addRoute('a', df::Vector(40, 7));
        k->addRoute('a', df::Vector(7, 40));
        l->addRoute('a', df::Vector(-11, 27));
    }

    started = 1;
    this->setPosition(df::Vector(-300, -300));
    // Pause start music.
    //p_music->pause();
    df::Sound* p_sound = RM.getSound("start");
    p_sound->play();
}

void GameStart::setWalls() {
    // room 'a'
    new Wall(df::Vector(-11, -11), df::Vector(-1, -11));
    new Wall(df::Vector(5, -11), df::Vector(15, -11));
    new Wall(df::Vector(-11, 15), df::Vector(-1, 15));
    new Wall(df::Vector(5, 15), df::Vector(15, 15));
    new Wall(df::Vector(-11, -11), df::Vector(-11, -1));
    new Wall(df::Vector(-11, 5), df::Vector(-11, 15));
    new Wall(df::Vector(15, -11), df::Vector(15, -1));
    new Wall(df::Vector(15, 5), df::Vector(15, 15));

    // room 'b'
    new Wall(df::Vector(-26, -6), df::Vector(-15, -6));
    new Wall(df::Vector(-26, 15), df::Vector(-15, 15));
    new Wall(df::Vector(-15, -6), df::Vector(-15, -1));
    new Wall(df::Vector(-15, 5), df::Vector(-15, 15));
    new Wall(df::Vector(-26, -6), df::Vector(-26, 4));
    new Wall(df::Vector(-26, 10), df::Vector(-26, 15));

    // hall between 'a' and 'b'
    new Wall(df::Vector(-15, -1), df::Vector(-11, -1));
    new Wall(df::Vector(-15, 5), df::Vector(-11, 5));

    // room 'c'
    new Wall(df::Vector(-6, -41), df::Vector(10, -41));
    new Wall(df::Vector(-6, -15), df::Vector(-1, -15));
    new Wall(df::Vector(5, -15), df::Vector(10, -15));
    new Wall(df::Vector(-6, -41), df::Vector(-6, -36));
    new Wall(df::Vector(-6, -30), df::Vector(-6, -15));
    new Wall(df::Vector(10, -41), df::Vector(10, -26));
    new Wall(df::Vector(10, -20), df::Vector(10, -15));

    // hall between 'a' and 'c'
    new Wall(df::Vector(-1, -15), df::Vector(-1, -11));
    new Wall(df::Vector(5, -15), df::Vector(5, -11));

    // room 'd'
    new Wall(df::Vector(19, -6), df::Vector(35, -6));
    new Wall(df::Vector(19, 15), df::Vector(35, 15));
    new Wall(df::Vector(35, -6), df::Vector(35, 4));
    new Wall(df::Vector(35, 10), df::Vector(35, 15));
    new Wall(df::Vector(19, -6), df::Vector(19, -1));
    new Wall(df::Vector(19, 5), df::Vector(19, 15));

    // hall between 'a' and 'd'
    new Wall(df::Vector(15, -1), df::Vector(19, -1));
    new Wall(df::Vector(15, 5), df::Vector(19, 5));

    // room 'e'
    new Wall(df::Vector(-6, 19), df::Vector(-1, 19));
    new Wall(df::Vector(5, 19), df::Vector(10, 19));
    new Wall(df::Vector(-6, 35), df::Vector(4, 35));
    new Wall(df::Vector(-6, 19), df::Vector(-6, 24));
    new Wall(df::Vector(-6, 30), df::Vector(-6, 35));
    new Wall(df::Vector(10, 19), df::Vector(10, 35));

    // hall between 'a' and 'e'
    new Wall(df::Vector(-1, 15), df::Vector(-1, 19));
    new Wall(df::Vector(5, 15), df::Vector(5, 19));

    // room 'f'
    new Wall(df::Vector(-46, -1), df::Vector(-41, -1));
    new Wall(df::Vector(-35, -1), df::Vector(-30, -1));
    new Wall(df::Vector(-46, 35), df::Vector(-41, 35));
    new Wall(df::Vector(-35, 35), df::Vector(-30, 35));
    new Wall(df::Vector(-46, -1), df::Vector(-46, 35));
    new Wall(df::Vector(-30, -1), df::Vector(-30, 4));
    new Wall(df::Vector(-30, 10), df::Vector(-30, 24));
    new Wall(df::Vector(-30, 30), df::Vector(-30, 35));

    // hall between 'b' and 'f'
    new Wall(df::Vector(-30, 4), df::Vector(-26, 4));
    new Wall(df::Vector(-30, 10), df::Vector(-26, 10));

    // room 'g'
    new Wall(df::Vector(-31, -41), df::Vector(-10, -41));
    new Wall(df::Vector(-31, -25), df::Vector(-26, -25));
    new Wall(df::Vector(-20, -25), df::Vector(-10, -25));
    new Wall(df::Vector(-31, -41), df::Vector(-31, -31));
    new Wall(df::Vector(-10, -41), df::Vector(-10, -36));
    new Wall(df::Vector(-10, -30), df::Vector(-10, -25));

    // hall between 'c' and 'g'
    new Wall(df::Vector(-10, -36), df::Vector(-6, -36));
    new Wall(df::Vector(-10, -30), df::Vector(-6, -30));

    // room 'i'
    new Wall(df::Vector(14, -36), df::Vector(35, -36));
    new Wall(df::Vector(14, -15), df::Vector(35, -15));
    new Wall(df::Vector(14, -36), df::Vector(14, -26));
    new Wall(df::Vector(14, -20), df::Vector(14, -15));
    new Wall(df::Vector(35, -36), df::Vector(35, -26));
    new Wall(df::Vector(35, -20), df::Vector(35, -15));

    // hall between 'c' and 'i'
    new Wall(df::Vector(10, -26), df::Vector(14, -26));
    new Wall(df::Vector(10, -20), df::Vector(14, -20));

    // room 'j'
    new Wall(df::Vector(39, -31), df::Vector(60, -31));
    new Wall(df::Vector(45, 25), df::Vector(60, 25));
    new Wall(df::Vector(39, -31), df::Vector(39, -26));
    new Wall(df::Vector(39, -20), df::Vector(39, 4));
    new Wall(df::Vector(39, 10), df::Vector(39, 25));
    new Wall(df::Vector(60, -31), df::Vector(60, 25));

    // hall between 'd' and 'j'
    new Wall(df::Vector(35, 4), df::Vector(39, 4));
    new Wall(df::Vector(35, 10), df::Vector(39, 10));

    // hall between 'i' and 'j'
    new Wall(df::Vector(35, -26), df::Vector(39, -26));
    new Wall(df::Vector(35, -20), df::Vector(39, -20));
}

int GameStart::draw() {
    return df::Object::draw();
}

//void GameStart::playMusic() {
//    p_music->play();
//}