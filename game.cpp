//
// game.cpp
//

// Engine includes.
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ViewObject.h"
#include "Vector.h"

#include "EnemyManager.h"
#include "Hero.h"
#include "Crystal.h"
#include "Bullet.h"
#include "Wall.h"
#include "Enemy.h"
#include "HealthPowerUp.h"
#include "FireratePowerUp.h"

int main(int argc, char* argv[]) {
    GM.startUp();
    LM.setLogLevel(-10);
    LM.setFlush();
    RM.loadSprite("sprites/hero-spr.txt", "hero");
    RM.loadSprite("sprites/crystal-spr.txt", "crystal");
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/wall-spr.txt", "wall");
    RM.loadSprite("sprites/health-powerup-spr.txt", "healthpowerup");
    RM.loadSprite("sprites/firerate-powerup-spr.txt", "fireratepowerup");
    
    Hero* p_hero = new Hero();
    new Crystal;
    new Enemy;
    new HealthPowerUp;
    new FireratePowerUp;
    new Bullet(df::Vector(0, 0));
    new Wall(df::Vector(5, 5), df::Vector(10, 5));
    new Wall(df::Vector(25, 5), df::Vector(15, 5));
    new Wall(df::Vector(5, 5), df::Vector(5, 15));
    EM.startUp();
    Room* a = new Room('a', df::Box(df::Vector(25, -5), 30, 30));
    Room* b = new Room('b', df::Box(df::Vector(0, 0), 20, 20));
    Room* c = new Room('c', df::Box(df::Vector(30, -30), 20, 20));
    Room* d = new Room('d', df::Box(df::Vector(60, 0), 20, 20));
    Room* e = new Room('e', df::Box(df::Vector(30, 30), 20, 20));
    a->addRoute('b', df::Vector(25, 10));
    a->addRoute('c', df::Vector(40, -5));
    a->addRoute('d', df::Vector(55, 10));
    a->addRoute('e', df::Vector(40, 25));
    b->addRoute('a', df::Vector(20, 10));
    c->addRoute('a', df::Vector(40, -10));
    d->addRoute('a', df::Vector(60, 10));
    e->addRoute('a', df::Vector(40, 30));
    WM.setViewFollowing(p_hero);
    WM.setBoundary(df::Box(df::Vector(-100, -100), 200, 200));
    GM.run();

    EM.shutDown();
    GM.shutDown();
}
