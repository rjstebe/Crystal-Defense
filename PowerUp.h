#include "Object.h"
#include "EventCollision.h"

class PowerUp : public df::Object {
private:
    void hit(const df::EventCollision* p_collision_event);

public:
    PowerUp();
    ~PowerUp();
    int eventHandler(const df::Event* p_e) override;
};