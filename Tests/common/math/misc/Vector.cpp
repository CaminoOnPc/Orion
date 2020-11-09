/*
	File: Vector.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "Vector.h"

Vector::Vector()
{
	x = y = z = 0.f;
}

Vector::Vector(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

float& Vector::operator[](int i) const
{
	return ((float*)this)[i];
}

Vector& Vector::operator=(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

Vector& Vector::operator+=(const Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector& Vector::operator*=(const Vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}

Vector& Vector::operator*=(const float& f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

Vector& Vector::operator/=(const Vector& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}

Vector& Vector::operator/=(const float& f)
{
	x /= f;
	y /= f;
	z /= f;

	return *this;
}

Vector Vector::operator+(const Vector& v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(const Vector& v) const
{
	return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vector::operator*(const float& f) const
{
	return Vector(x * f, y * f, z * f);
}

Vector Vector::operator/(const Vector& v) const
{
	return Vector(x / (v.x), y / (v.y), z / (v.z));
}

Vector Vector::operator/(const float& f) const
{
	return Vector(x / (f), y / (f), z / (f));
}

bool Vector::operator==(const Vector& v) const
{
	return v.x == x && v.y == y && v.z == z;
}

bool Vector::operator!=(const Vector& e) const
{
	return e.x != x || e.y != y || e.z != z;
}

float Vector::Distance(Vector v)
{
	return (*this - (v)).Length();
}

float Vector::Length(void) const
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector::Length2D(void) const
{
	return sqrtf(x * x + y * y);
}