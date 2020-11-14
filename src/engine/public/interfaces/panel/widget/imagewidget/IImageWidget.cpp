/*
	File: IImageWidget.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IImageWidget.h"

//-----------------------------------------------------------------------------
// Activates IImageWidget initalization process
//-----------------------------------------------------------------------------
void IImageWidget::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_Widget = new wiSprite();

	m_RenderPath = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	m_RenderPath->AddSprite(&*m_Widget);
}

//-----------------------------------------------------------------------------
// Activates IImageWidget shutdown process
//-----------------------------------------------------------------------------
void IImageWidget::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IImageWidget
//-----------------------------------------------------------------------------
void IImageWidget::Run(float dt)
{
	return;
}

//-----------------------------------------------------------------------------
// Sets a widget position
//-----------------------------------------------------------------------------
void IImageWidget::SetPos(float x, float y)
{
	m_Position = Vector(x, y, 0.0f);

	m_Widget->params.pos = XMFLOAT3(x, y, 0.0f);
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void IImageWidget::GetPos(float& x, float& y)
{
	x = m_Widget->params.pos.x;
	y = m_Widget->params.pos.y;
}

//-----------------------------------------------------------------------------
// Sets a widget size
//-----------------------------------------------------------------------------
void IImageWidget::SetSize(float width, float height)
{
	m_Size = Vector(width, height, 0.0f);

	m_Widget->params.siz = XMFLOAT2(width, height);
}

//-----------------------------------------------------------------------------
// Returns a widget size
//-----------------------------------------------------------------------------
void IImageWidget::GetSize(float& width, float& height)
{
	height = m_Size.y;
	width = m_Size.x;
}

//-----------------------------------------------------------------------------
// Sets a widget visibility
//-----------------------------------------------------------------------------
void IImageWidget::SetHidden(bool hidden)
{
	m_Hidden = hidden;

	m_Widget->SetHidden(m_Hidden);
}

//-----------------------------------------------------------------------------
// Returns a widget visibility
//-----------------------------------------------------------------------------
void IImageWidget::GetHidden(bool& hidden)
{
	hidden = m_Hidden;
}

//-----------------------------------------------------------------------------
// Sets a widget image
//-----------------------------------------------------------------------------
void IImageWidget::SetImage(const char* image)
{
	m_Image = image;

	m_RenderPath->RemoveSprite(m_Widget);

	m_Widget = new wiSprite(image);
	m_RenderPath->AddSprite(&*m_Widget);
}

//-----------------------------------------------------------------------------
// Returns a widget image
//-----------------------------------------------------------------------------
void IImageWidget::GetImage(const char*& image)
{
	image = m_Image;
}

//-----------------------------------------------------------------------------
// Sets a widget color
//-----------------------------------------------------------------------------
void IImageWidget::SetColor(Color color)
{
	m_Color = color;

	m_RenderPath->RemoveSprite(m_Widget);

	m_Widget = new wiSprite();
	m_RenderPath->AddSprite(&*m_Widget);

	m_Widget->params.color = XMFLOAT4(color.rBase(), color.gBase(), color.bBase(), color.aBase());
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void IImageWidget::GetColor(Color& color)
{
	color = m_Color;
}

//-----------------------------------------------------------------------------
// Updates a widget
//-----------------------------------------------------------------------------
void IImageWidget::Update()
{
	
}
