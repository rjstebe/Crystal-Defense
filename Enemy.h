#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"

class Enemy : public df::Object {
private:
    void hit(const df::EventCollision* p_collision_event);
    void step();
    float speed = 1;
    float attack_period = 5;
    float attack_cooldown = attack_period;
public:

    Enemy();
    ~Enemy();
    int eventHandler(const df::Event* p_e) override;
};