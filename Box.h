#pragma once

#include "Vector.h"

namespace df {

class Box {
private:
	Vector m_corner = Vector(); // Upper left corner of box.
	float m_horizontal = 0;     // Horizontal dimension.
	float m_vertical = 0;       // Vertical dimension.

public:
	// Create box with (0, 0) for the corner, and 0 for horiz and vert.
	Box();

	// Create box with an upper-left corner, horiz and vert sizes.
	Box(Vector init_corner, float init_horizontal, float init_vertical);

	// Set upper left corner of box.
	void setCorner(Vector new_corner);

	// Get upper left corner box.
	Vector getCorner() const;

	// Set horizontal size of box.
	void setHorizontal(float new_horizontal);

	// Get horizontal size of box.
	float getHorizontal() const;

	// Set vertical size of box.
	void setVertical(float new_vertical);

	// Get vertical size of box.
	float getVertical() const;
};

}