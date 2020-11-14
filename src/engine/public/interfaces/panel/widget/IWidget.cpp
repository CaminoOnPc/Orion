/*
	File: IWidget.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IWidget.h"

//-----------------------------------------------------------------------------
// Activates IWidget initalization process
//-----------------------------------------------------------------------------
void IWidget::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IWidget shutdown process
//-----------------------------------------------------------------------------
void IWidget::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IWidget
//-----------------------------------------------------------------------------
void IWidget::Run(float dt)
{
	return;
}

//-----------------------------------------------------------------------------
// Returns a screen position
//-----------------------------------------------------------------------------
void IWidget::GetScreenPos(float& x, float& y)
{
}

//-----------------------------------------------------------------------------
// Returns a screen size
//-----------------------------------------------------------------------------
void IWidget::GetScreenSize(float& height, float& width)
{
	height = m_Interface->m_Base->m_Settings->m_height;
	width = m_Interface->m_Base->m_Settings->m_width;
}

//-----------------------------------------------------------------------------
// Creates a font handle
//-----------------------------------------------------------------------------
HFont* IWidget::CreateFont(const char* font, int size, int flags)
{
	std::string fontPath = "data/game/materials/opentype/";
	fontPath.append(font);

	return new HFont(font, size, flags, wiFont::AddFontStyle(fontPath));
}