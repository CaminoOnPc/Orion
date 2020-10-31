/*
	File: Color.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

class Color
{
public:
	Color()
	{
		*((int*)this) = 0;
	}

	Color(int color32)
	{
		*((int*)this) = color32;
	}

	Color(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b, 255);
	}

	Color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 255)
	{
		m_Color[0] = (unsigned char)_r;
		m_Color[1] = (unsigned char)_g;
		m_Color[2] = (unsigned char)_b;
		m_Color[3] = (unsigned char)_a;
	}

	void GetColor(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = m_Color[0];
		_g = m_Color[1];
		_b = m_Color[2];
		_a = m_Color[3];
	}

	unsigned char& operator[](int index)
	{
		return m_Color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return m_Color[index];
	}

	bool operator == (const Color& rhs) const
	{
		return (*((int*)this) == *((int*)&rhs));
	}

	bool operator != (const Color& rhs) const
	{
		return !(operator==(rhs));
	}

	float Hue() const
	{
		if (m_Color[0] == m_Color[1] && m_Color[1] == m_Color[2])
		{
			return 0.0f;
		}

		float r = m_Color[0] / 255.0f;
		float g = m_Color[1] / 255.0f;
		float b = m_Color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if (r == max)
		{
			hue = (g - b) / delta;
		}
		else if (g == max)
		{
			hue = 2 + (b - r) / delta;
		}
		else if (b == max)
		{
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.0f)
		{
			hue += 360.0f;
		}
		return hue;
	}

	float Saturation() const
	{
		float r = m_Color[0] / 255.0f;
		float g = m_Color[1] / 255.0f;
		float b = m_Color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if (max != min)
		{
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}

	float Brightness() const
	{
		float r = m_Color[0] / 255.0f;
		float g = m_Color[1] / 255.0f;
		float b = m_Color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	inline int r() const
	{
		return m_Color[0];
	}

	inline int g() const
	{
		return m_Color[1];
	}

	inline int b() const
	{
		return m_Color[2];
	}

	inline int a() const
	{
		return m_Color[3];
	}

	inline float rBase() const
	{
		return m_Color[0] / 255.0f;
	}

	inline float gBase() const
	{
		return m_Color[1] / 255.0f;
	}

	inline float bBase() const
	{
		return m_Color[2] / 255.0f;
	}

	inline float aBase() const
	{
		return m_Color[3] / 255.0f;
	}
private:
	unsigned char m_Color[4];
};