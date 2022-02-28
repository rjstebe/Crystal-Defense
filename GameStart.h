#include "ViewObject.h"
//#include "Music.h"

class GameStart : public df::ViewObject {

private:
    void start();
    void setWalls();
    //df::Music* p_music;
    int started;

public:
    GameStart();
    void GameDone();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
    //void playMusic();
};