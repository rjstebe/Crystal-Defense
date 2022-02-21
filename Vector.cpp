#include <math.h>

#include "Vector.h"

// Create Vector with (x, y).
df::Vector::Vector(float init_x, float init_y) {
	setXY(init_x, init_y);
}

// Default 2D (x, y) is (0, 0).
df::Vector::Vector() {
	setXY(0, 0);
}

// Set horizontal component.
void df::Vector::setX(float new_x) {
	m_x = new_x;
}

// Get horizontal component.
float df::Vector::getX() const {
	return m_x;
}

// Set vertical component.
void df::Vector::setY(float new_y) {
	m_y = new_y;
}

// Get vertical component.
float df::Vector::getY() const {
	return m_y;
}

// Set horizontal & vertical components.
void df::Vector::setXY(float new_x, float new_y) {
	setX(new_x);
	setY(new_y);
}

// Return magnitude of vector.
float df::Vector::getMagnitude() const {
	return sqrt(m_x * m_x + m_y * m_y);
}

// Normalize vector.
void df::Vector::normalize() {
	float length = getMagnitude();
	if (length > 0) {
		setXY(m_x / length, m_y / length);
	}
}

// Scale vector.
void df::Vector::scale(float s) {
	setXY(m_x * s, m_y * s);
}

// Add two Vectors, return new Vector.
df::Vector df::Vector::operator+(const Vector& other) const {
	return Vector(m_x + other.m_x, m_y + other.m_y);
}

// Subtract two Vectors, return new Vector.
df::Vector df::Vector::operator-(const Vector& other) const {
	return *this + !other;
}

// Multiply two Vectors, return new Vector (uses dot multiplication).
df::Vector df::Vector::operator*(const Vector& other) const {
	return Vector(m_x * other.m_x, m_y * other.m_y);
}

// Divide two Vectors, return new Vector (uses dot multiplication).
df::Vector df::Vector::operator/(const Vector& other) const {
	return Vector(m_x / other.m_x, m_y / other.m_y);
}

// Compares two Vectors, returns true if they are equal.
bool df::Vector::operator==(const Vector& other) const {
	return m_x == other.m_x && m_y == other.m_y;
}

// Negates a Vector, return new Vector.
df::Vector df::Vector::operator!() const {
	Vector v = *this;
	v.scale(-1);
	return v;
}
