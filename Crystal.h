#include "Object.h"

// Engine includes.
#include "EventCollision.h"
#include "ViewObject.h"

const int CRYSTAL_HEALTH = 100;

class Crystal : public df::Object {
private:
    void hit(const df::EventCollision* p_collision_event);
    int health = CRYSTAL_HEALTH;
    df::ViewObject* health_tracker = NULL;
public:
    Crystal();
    ~Crystal();
    int eventHandler(const df::Event* p_e) override;
};