#include "ViewObject.h"
#ifndef __RETICLE_H__
#define __RETICLE_H__
#define RETICLE_CHAR '+'

class Reticle : public df::ViewObject {

public:
    Reticle();
    int draw() override;
    int eventHandler(const df::Event* p_e) override;
};
#endif // !__RETICLE_H__

