//
// game.cpp
//

// Engine includes.
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Object.h"
#include "Hero.h"
#include "Vector.h"
#include "Crystal.h"
#include "Bullet.h"
#include "Wall.h"
#include "Enemy.h"

int main(int argc, char* argv[]) {
    GM.startUp();
    LM.setFlush();
    RM.loadSprite("sprites/pole.txt", "pole");
    RM.loadSprite("sprites/hero-spr.txt", "hero");
    RM.loadSprite("sprites/crystal-spr.txt", "crystal");
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/wall-spr.txt", "wall");
    
    class TestObj : public df::Object {
    public:
        TestObj() {
            setSprite("pole");
            setPosition(df::Vector(10, 10));
        }
    };
    new TestObj;
    new Hero;
    new Crystal;
    new Enemy;
    new Bullet(df::Vector(0, 0));
    new Wall;
    GM.run();

    GM.shutDown();

}
