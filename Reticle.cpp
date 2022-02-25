#include "Reticle.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Vector.h"
#include "utility.h"

Reticle::Reticle() {
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

    int world_horiz = (int)WM.getBoundary().getHorizontal();
    int world_vert = (int)WM.getBoundary().getVertical();
    df::Vector p(world_horiz / 2, world_vert / 2);
    setPosition(p);
}

int Reticle::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            // Change location to new mouse position.
            setPosition(pixelsToSpaces(p_mouse_event->getMousePosition()));
            return 1;
        }
    }
    // If get here, have ignored this event.
    return 0;
}

int Reticle::draw() {
    LM.writeLog(-10, "Reticle::draw(): drew reticle");
    return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}