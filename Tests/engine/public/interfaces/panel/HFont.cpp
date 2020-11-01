/*
    File: HFont.cpp

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "HFont.h"

//-----------------------------------------------------------------------------
// Creates HFont font handle
//-----------------------------------------------------------------------------
HFont::HFont(const char* font, int size, int flags)
{
	int length = strlen(font);

	m_Name = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, font, -1, m_Name, length);

	m_Font.m_Name = m_Name;
	m_Font.m_Size = size;
	m_Font.m_Flag = flags;
}

//-----------------------------------------------------------------------------
// Destroys HFont font handle
//-----------------------------------------------------------------------------
HFont::~HFont()
{
	SafeRelease(&m_Name);
	delete[] m_Name;
}