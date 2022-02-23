#include "Object.h"
#ifndef __RETICLE_H__
#define __RETICLE_H__
#define RETICLE_CHAR '+'

class Reticle : public df::Object {

public:
    Reticle();
    int draw(void) override;
    int eventHandler(const df::Event* p_e) override;
};
#endif // !__AIMER_H__

