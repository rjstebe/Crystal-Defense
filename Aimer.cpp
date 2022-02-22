#include "Aimer.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Vector.h"

Aimer::Aimer() {
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

    int world_horiz = (int)WM.getBoundary().getHorizontal();
    int world_vert = (int)WM.getBoundary().getVertical();
    df::Vector p(world_horiz / 2, world_vert / 2);
    setPosition(p);
}

int Aimer::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            // Change location to new mouse position.
            LM.writeLog("event, %d %d", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY());

            setPosition(p_mouse_event->getMousePosition());
            draw();
            return 1;
        }
        if (p_mouse_event->getMouseAction() == df::CLICKED) {
            // Change location to new mouse position.
            LM.writeLog("Click event, %d %d", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY());

            setPosition(p_mouse_event->getMousePosition());
            draw();
            return 1;
        }
    }

    // If get here, have ignored this event.
    return 0;
}

int Aimer::draw() {
    LM.writeLog("ret, %i %i", getPosition().getX(), getPosition().getY());
    DM.drawCh(df::Vector(20,20), 'X', df::RED);
    return DM.drawCh(getPosition(), AIMER_CHAR, df::RED);
}