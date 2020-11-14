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

	m_RenderPath = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;

	m_Data.m_Color = Color(255, 255, 255, 255);
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
	m_Data.m_Position = Vector(x, y, 0.0f);
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void ITextWidget::GetPos(float& x, float& y)
{
	x = m_Data.m_Position.x;
	y = m_Data.m_Position.y;
}

//-----------------------------------------------------------------------------
// Sets a widget size
//-----------------------------------------------------------------------------
void ITextWidget::SetSize(int size)
{
	m_Data.m_Size = size;

	Update();
}

//-----------------------------------------------------------------------------
// Returns a widget size
//-----------------------------------------------------------------------------
void ITextWidget::GetSize(int& size)
{
	size = m_Data.m_Size;
}

//-----------------------------------------------------------------------------
// Sets a widget visibility
//-----------------------------------------------------------------------------
void ITextWidget::SetHidden(bool hidden)
{
	m_Data.m_Hidden = hidden;

	Update();
}

//-----------------------------------------------------------------------------
// Returns a widget visibility
//-----------------------------------------------------------------------------
void ITextWidget::GetHidden(bool& hidden)
{
	hidden = m_Data.m_Hidden;
}

//-----------------------------------------------------------------------------
// Sets a widget text
//-----------------------------------------------------------------------------
void ITextWidget::SetText(std::string text)
{
	m_Data.m_Text = text;

	Update();
}

//-----------------------------------------------------------------------------
// Returns a widget text
//-----------------------------------------------------------------------------
void ITextWidget::GetText(std::string& text)
{
	text = m_Widget->GetTextA();
}

//-----------------------------------------------------------------------------
// Sets a widget color
//-----------------------------------------------------------------------------
void ITextWidget::SetColor(Color color)
{
	m_Data.m_Color = color;

	Update();
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void ITextWidget::GetColor(Color& color)
{
	color = m_Data.m_Color;
}

//-----------------------------------------------------------------------------
// Sets a widget font
//-----------------------------------------------------------------------------
void ITextWidget::SetFont(HFont* font)
{
	m_Data.m_Font = font;

	Update();
}

//-----------------------------------------------------------------------------
// Returns a widget font
//-----------------------------------------------------------------------------
void ITextWidget::GetFont(HFont*& font)
{
	font = m_Data.m_Font;
}

//-----------------------------------------------------------------------------
// Updates a widget
//-----------------------------------------------------------------------------
void ITextWidget::Update()
{
	m_RenderPath->RemoveFont(m_Widget);

	m_Widget = new wiSpriteFont();
	m_RenderPath->AddFont(&*m_Widget);

	if (!m_Data.m_Text.empty())
	{
		m_Widget->SetText(m_Data.m_Text);
	}

	if (m_Data.m_Font)
	{
		m_Widget->params.style = m_Data.m_Font->m_Font.m_Style;
		m_Widget->params.size = m_Data.m_Font->m_Font.m_Size;

		if (m_Data.m_Font->m_Font.m_Flag && IWidget::EFontFlags::FONTFLAGS_OUTLINE)
		{
			m_Widget->params.outlineColor = wiColor::Black();
		}

		if (m_Data.m_Font->m_Font.m_Flag && IWidget::EFontFlags::FONTFLAGS_SHADOW)
		{
			m_Widget->params.shadowColor = wiColor::Black();
		}
	}

	m_Widget->params.color = wiColor(m_Data.m_Color.r(), m_Data.m_Color.g(), m_Data.m_Color.b(), m_Data.m_Color.a());
	m_Widget->params.posX = m_Data.m_Position.x;
	m_Widget->params.posY = m_Data.m_Position.y;

	m_Widget->params.size = m_Data.m_Size;

	m_Widget->SetHidden(m_Data.m_Hidden);
}
