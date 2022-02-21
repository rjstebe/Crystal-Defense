#pragma once

namespace df {

class Vector {
private:
	float m_x; // Horizontal Component.
	float m_y; // Vertical Component.

public:
	// Create Vector with (x, y).
	Vector(float init_x, float init_y);

	// Default 2D (x, y) is (0, 0).
	Vector();

	// Set horizontal component.
	void setX(float new_x);

	// Get horizontal component.
	float getX() const;

	// Set vertical component.
	void setY(float new_y);

	// Get vertical component.
	float getY() const;

	// Set horizontal & vertical components.
	void setXY(float new_x, float new_y);

	// Return magnitude of vector.
	float getMagnitude() const;

	// Normalize vector.
	void normalize();

	// Scale vector.
	void scale(float s);

	// Add two Vectors, return new Vector.
	Vector operator+(const Vector& other) const;

	// Subtract two Vectors, return new Vector.
	Vector operator-(const Vector& other) const;

	// Multiply two Vectors, return new Vector (uses dot multiplication).
	Vector operator*(const Vector& other) const;

	// Divide two Vectors, return new Vector (uses dot multiplication).
	Vector operator/(const Vector& other) const;

	// Compares two Vectors, returns true if they are equal.
	bool operator==(const Vector& other) const;

	// Negates a Vector, return new Vector.
	Vector operator!() const;
};

}

