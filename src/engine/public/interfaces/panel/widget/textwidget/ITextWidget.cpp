/*
	File: ITextWidget.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "ITextWidget.h"

//-----------------------------------------------------------------------------
// Activates ITextWidget initalization process
//-----------------------------------------------------------------------------
void ITextWidget::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_Widget = new wiSpriteFont();

	m_RenderPath = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	m_RenderPath->AddFont(&*m_Widget);
}

//-----------------------------------------------------------------------------
// Activates ITextWidget shutdown process
//-----------------------------------------------------------------------------
void ITextWidget::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of ITextWidget
//-----------------------------------------------------------------------------
void ITextWidget::Run(float dt)
{
	return;
}

//-----------------------------------------------------------------------------
// Sets a widget position
//-----------------------------------------------------------------------------
void ITextWidget::SetPos(float x, float y)
{
	m_Widget->params.posX = x;
	m_Widget->params.posY = y;
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void ITextWidget::GetPos(float& x, float& y)
{
	x = m_Widget->params.posX;
	y = m_Widget->params.posY;
}

//-----------------------------------------------------------------------------
// Sets a widget size
//-----------------------------------------------------------------------------
void ITextWidget::SetSize(int size)
{
	m_Widget->params.size = size;
}

//-----------------------------------------------------------------------------
// Returns a widget size
//-----------------------------------------------------------------------------
void ITextWidget::GetSize(int& size)
{
	size = m_Widget->params.size;
}

//-----------------------------------------------------------------------------
// Sets a widget text
//-----------------------------------------------------------------------------
void ITextWidget::SetText(const char* text)
{
	m_Widget->SetText(text);
}

//-----------------------------------------------------------------------------
// Returns a widget text
//-----------------------------------------------------------------------------
void ITextWidget::GetText(const char*& text)
{
	text = m_Widget->GetTextA().c_str();
}

//-----------------------------------------------------------------------------
// Sets a widget font
//-----------------------------------------------------------------------------
void ITextWidget::SetFont(HFont* font)
{
	m_RenderPath->RemoveFont(m_Widget);

	m_Widget = new wiSpriteFont();
	m_RenderPath->AddFont(&*m_Widget);

	m_Widget->params.style = font->m_Font.m_Style;
	m_Widget->params.size = font->m_Font.m_Size;

	if (font->m_Font.m_Flag && IWidget::EFontFlags::FONTFLAGS_OUTLINE)
	{
		m_Widget->params.outlineColor = wiColor::Black();
	}

	if (font->m_Font.m_Flag && IWidget::EFontFlags::FONTFLAGS_SHADOW)
	{
		m_Widget->params.shadowColor = wiColor::Black();
	}

	m_Font = font;
}

//-----------------------------------------------------------------------------
// Returns a widget font
//-----------------------------------------------------------------------------
void ITextWidget::GetFont(HFont*& font)
{
	font = m_Font;
}