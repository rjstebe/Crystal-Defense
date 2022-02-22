#include "Object.h"
#include "EventCollision.h"

class Crystal : public df::Object {
private:
    void hit(const df::EventCollision* p_collision_event);
    int health;
public:
    Crystal();
    ~Crystal();
    int eventHandler(const df::Event* p_e) override;
};