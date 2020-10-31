/*
	File: Vector.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

class Vector
{
public:
	float	x, y, z;

	Vector(void);
	Vector(float x, float y, float z);

	float& operator[](int) const;
	Vector& operator=(const Vector&);

	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector& operator*=(const Vector&);
	Vector& operator*=(const float&);
	Vector& operator/=(const Vector&);
	Vector& operator/=(const float&);

	Vector	operator+(const Vector&) const;
	Vector	operator-(const Vector&) const;
	Vector	operator*(const Vector&) const;
	Vector	operator*(const float&) const;
	Vector	operator/(const Vector&) const;
	Vector	operator/(const float&) const;

	bool operator==(const Vector&) const;
	bool operator!=(const Vector&) const;
};