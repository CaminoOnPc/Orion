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
// Sets a widget image
//-----------------------------------------------------------------------------
void IImageWidget::SetImage(const char* image)
{
	m_RenderPath->RemoveSprite(m_Widget);

	m_Widget = new wiSprite(image);
	m_RenderPath->AddSprite(&*m_Widget);
}

//-----------------------------------------------------------------------------
// Returns a widget image
//-----------------------------------------------------------------------------
void IImageWidget::GetImage(const char*& image)
{

}

//-----------------------------------------------------------------------------
// Sets a widget color
//-----------------------------------------------------------------------------
void IImageWidget::SetColor(Color color)
{
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
	color = Color(m_Widget->params.color.x, m_Widget->params.color.y, m_Widget->params.color.z, m_Widget->params.color.w);
}

//-----------------------------------------------------------------------------
// Sets a widget position
//-----------------------------------------------------------------------------
void IImageWidget::SetPos(float x, float y)
{
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
void IImageWidget::SetSize(float height, float width)
{
	m_Widget->params.siz = XMFLOAT2(height, width);
}

//-----------------------------------------------------------------------------
// Returns a widget size
//-----------------------------------------------------------------------------
void IImageWidget::GetSize(float& height, float& width)
{
	height = m_Widget->params.siz.y;
	width = m_Widget->params.siz.x;
}

//-----------------------------------------------------------------------------
// Sets a widget rotation
//-----------------------------------------------------------------------------
void IImageWidget::SetRotation(float roll)
{
	m_Widget->params.rotation = roll;
}

//-----------------------------------------------------------------------------
// Returns a widget rotation
//-----------------------------------------------------------------------------
void IImageWidget::GetRotation(float& roll)
{
	roll = m_Widget->params.rotation;
}

//-----------------------------------------------------------------------------
// Sets a widget scale
//-----------------------------------------------------------------------------
void IImageWidget::SetScale(float height, float width)
{
	m_Widget->params.scale.y = height;
	m_Widget->params.scale.x = width;
}

//-----------------------------------------------------------------------------
// Returns a widget scale
//-----------------------------------------------------------------------------
void IImageWidget::GetScale(float& height, float& width)
{
	height = m_Widget->params.scale.y;
	width = m_Widget->params.scale.x;
}