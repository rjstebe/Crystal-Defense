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
#include "GameStart.h"

void populateWorld(void);

int main(int argc, char* argv[]) {
    GM.startUp();
    LM.setLogLevel(0);
    LM.setFlush();
    RM.loadSprite("sprites/hero-spr.txt", "hero");
    RM.loadSprite("sprites/crystal-spr.txt", "crystal");
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/wall-spr.txt", "wall");
    RM.loadSprite("sprites/health-powerup-spr.txt", "healthpowerup");
    RM.loadSprite("sprites/firerate-powerup-spr.txt", "fireratepowerup");
    RM.loadSprite("sprites/start-spr.txt", "gamestart");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/enemy-death.wav", "enemydeath");
    RM.loadSound("sounds/health-power.wav", "healthup");
    RM.loadSound("sounds/shoot-power.wav", "shootup");
    RM.loadSound("sounds/game-start.wav", "start");
    RM.loadSound("sounds/game-over.wav", "over");
    RM.loadSound("sounds/player-spawn.wav", "playerspawn");
    RM.loadSound("sounds/player-damage.wav", "playerdamage");
    populateWorld();
    
    //EM.startUp();


    GM.run();

    EM.shutDown();
    GM.shutDown();
}

void populateWorld(void) {

    // Spawn GameStart object.
    new GameStart();

}