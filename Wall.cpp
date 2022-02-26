#include "Wall.h"
#include "DisplayManager.h"
#include "LogManager.h"

Wall::Wall(df::Vector end1, df::Vector end2)
{
	this->end1 = end1;
	this->end2 = end2;
	df::Vector temp;
	setSprite("wall");
	if (this->end1.getY() - this->end2.getY() == 0) {
		length = abs(this->end1.getX() - this->end2.getX());
		dir = 1; // horizontal wall
		if (end1.getY() > end2.getY()) {
			temp.setXY(this->end2.getX(), this->end2.getY());
			this->end2.setXY(this->end1.getX(), this->end1.getY());
			this->end1.setXY(this->end2.getX(), this->end2.getY());
		}
		setBox(df::Box(pixelsToSpaces(this->end1), this->length, 1));
	}
	else{
		length = abs(this->end1.getY() - this->end2.getY());
		dir = 0; // vertical wall
		if (end1.getX() > end2.getX()) {
			temp.setXY(this->end2.getX(), this->end2.getY());
			this->end2.setXY(this->end1.getX(), this->end1.getY());
			this->end1.setXY(this->end2.getX(), this->end2.getY());
			
		}
		setBox(df::Box(pixelsToSpaces(this->end1),1,this->length));
	}
	setType("Wall");
	setPosition(end1);

}

Wall::~Wall()
{
}

int Wall::draw(void)
{
	if (dir) { // horizontal wall
		for (int i = 0; i < length; i++) {
			DM.drawCh(df::Vector(getPosition().getX() + i, getPosition().getY()), '#', df::WHITE);
		}
	}
	else { // vertical wall
		for (int i = 0; i < length; i++) {
			DM.drawCh(df::Vector(getPosition().getX(), getPosition().getY() + i), '#', df::WHITE);
		}
	}
	return 	1;
}
