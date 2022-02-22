#include "Object.h"
#ifndef __AIMER_H__
#define __AIMER_H__
#define AIMER_CHAR '+'

class Aimer : public df::Object {

public:
    Aimer();
    int draw(void) override;
    int eventHandler(const df::Event* p_e) override;
};
#endif // !__AIMER_H__

