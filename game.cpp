//
// game.cpp
//

// Engine includes.
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Object.h"
#include "ViewObject.h"
#include "Vector.h"

#include "Hero.h"
#include "Crystal.h"
#include "Bullet.h"
#include "Wall.h"
#include "Enemy.h"

int main(int argc, char* argv[]) {
    GM.startUp();
    //LM.setLogLevel(-5);
    LM.setFlush();
    RM.loadSprite("sprites/hero-spr.txt", "hero");
    RM.loadSprite("sprites/crystal-spr.txt", "crystal");
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/wall-spr.txt", "wall");
    
    df::ViewObject* crystal_health = new df::ViewObject();
    crystal_health->setColor(df::CYAN);
    crystal_health->setLocation(df::TOP_LEFT);
    crystal_health->setViewString("crystal");
    crystal_health->setValue(CRYSTAL_HEALTH);
    df::ViewObject* player_health = new df::ViewObject();
    player_health->setColor(df::RED);
    player_health->setLocation(df::TOP_CENTER);
    player_health->setViewString("health");
    player_health->setValue(PLAYER_HEALTH);
    new Hero;
    new Crystal;
    new Enemy;
    new Bullet(df::Vector(0, 0));
    new Wall;
    GM.run();

    GM.shutDown();

}
