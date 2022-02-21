#include "Object.h"
#include "EventCollision.h"

class Enemy : public df::Object {
private:
    void hit(const df::EventCollision* p_collision_event);
public:

    Enemy();
    ~Enemy();
    int eventHandler(const df::Event* p_e) override;
};