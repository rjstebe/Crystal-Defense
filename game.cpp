//
// game.cpp
//

// Engine includes.
#include "LogManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Object.h"

int main(int argc, char* argv[]) {
    GM.startUp();
    LM.setFlush();
    RM.loadSprite("sprites/pole.txt", "pole");
    
    class TestObj : public df::Object {
    public:
        TestObj() {
            setSprite("pole");
            setPosition(df::Vector(10, 10));
        }
    };
    new TestObj;
    GM.run();

    GM.shutDown();

}
