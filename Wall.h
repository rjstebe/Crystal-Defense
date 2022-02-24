#include "Object.h"

class Wall : public df::Object {
private:
    df::Vector end1;
    df::Vector end2;
    int length;
    int dir; // 0 for horizontal, 1 for vertical
public:
    Wall(df::Vector end1, df::Vector end2);
    ~Wall();
    int draw(void) override;
};