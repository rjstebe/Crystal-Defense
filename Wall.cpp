#include "Wall.h"
#include "DisplayManager.h"
#include "LogManager.h"

Wall::Wall(df::Vector side1, df::Vector side2)
{
	this->end1 = side1;
	this->end2 = side2;
	setSprite("wall");
	if (this->end1.getY() - this->end2.getY() == 0) {
		length = abs(this->end1.getX() - this->end2.getX());
		dir = 1; // horizontal wall
		if (end1.getX() > end2.getX()) {
			this->end2.setX(side1.getX());
			this->end1.setX(side2.getX());
		}
		LM.writeLog("end1 %f", end1.getX());
		LM.writeLog("length %i", this->length);
		setBox(df::Box(pixelsToSpaces(this->end1 + df::Vector(-0.5, 0.5)), this->length+1, 1));
	}
	else{
		length = abs(this->end1.getY() - this->end2.getY());
		dir = 0; // vertical wall
		if (end1.getY() > end2.getY()) {
			this->end2.setY(side1.getY());
			this->end1.setY(side2.getY());
		}
		setBox(df::Box(pixelsToSpaces(this->end1 + df::Vector(-0.5, 0.5)), 1, this->length + 1));
	}
	setType("Wall");
	setPosition(end1);
	setAltitude(3);
	LM.writeLog("pos %f %f ", getBox().getCorner().getX(), getBox().getCorner().getY());
}

Wall::~Wall()
{
}

int Wall::draw(void)
{
	if (dir) { // horizontal wall
		for (int i = 0; i < length; i++) {
			DM.drawCh(df::Vector(getPosition().getX() + i, getPosition().getY()), '#', df::WHITE);
			DM.drawCh(getBox().getCorner(), '#', df::RED);
		}
	}
	else { // vertical wall
		for (int i = 0; i < length; i++) {
			DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + i), '#', df::WHITE);
		}
	}
	return 	1;
}
