/*
	File: IGradientWidget.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IGradientWidget.h"

//-----------------------------------------------------------------------------
// Activates IGradientWidget initalization process
//-----------------------------------------------------------------------------
void IGradientWidget::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_RenderPath = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
}

//-----------------------------------------------------------------------------
// Activates IGradientWidget shutdown process
//-----------------------------------------------------------------------------
void IGradientWidget::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IGradientWidget
//-----------------------------------------------------------------------------
void IGradientWidget::Run(float dt)
{
	return;
}

//-----------------------------------------------------------------------------
// Sets a widget position
//-----------------------------------------------------------------------------
void IGradientWidget::SetPos(float x, float y, bool immedUpdate)
{
	m_Data.m_Position = Vector(x, y, 0.0f);

	if (immedUpdate)
	{
		Update();
	}
	else
	{

	}
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void IGradientWidget::GetPos(float& x, float& y)
{
	x = m_Data.m_Position.x;
	y = m_Data.m_Position.y;
}

//-----------------------------------------------------------------------------
// Sets a widget size
//-----------------------------------------------------------------------------
void IGradientWidget::SetSize(float width, float height, bool immedUpdate)
{
	m_Data.m_Size = Vector(width, height, 0.0f);

	if (immedUpdate)
	{
		Update();
	}
	else
	{

	}
}

//-----------------------------------------------------------------------------
// Returns a widget size
//-----------------------------------------------------------------------------
void IGradientWidget::GetSize(float& width, float& height)
{
	height = m_Data.m_Size.y;
	width = m_Data.m_Size.x;
}

//-----------------------------------------------------------------------------
// Sets a widget visibility
//-----------------------------------------------------------------------------
void IGradientWidget::SetHidden(bool hidden, bool immedUpdate)
{
	m_Data.m_Hidden = hidden;

	if (immedUpdate)
	{
		Update();
	}
	else
	{
		for (size_t i = 0; i < m_Widgets.capacity(); i++)
		{
			if (m_Widgets[i])
			{
				m_Widgets[i]->SetHidden(hidden);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Returns a widget visibility
//-----------------------------------------------------------------------------
void IGradientWidget::GetHidden(bool& hidden)
{
	hidden = m_Data.m_Hidden;
}

//-----------------------------------------------------------------------------
// Sets a widget color
//-----------------------------------------------------------------------------
void IGradientWidget::SetColor(Color start, Color end, bool immedUpdate)
{
	m_Data.m_Start = start;
	m_Data.m_End = end;

	if (immedUpdate)
	{
		Update();
	}
	else
	{
		
	}
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void IGradientWidget::GetColor(Color& start, Color& end)
{
	start = m_Data.m_Start;
	end = m_Data.m_End;
}

//-----------------------------------------------------------------------------
// Updates a widget
//-----------------------------------------------------------------------------
void IGradientWidget::Update()
{
	for (size_t i = 0; i < m_Widgets.capacity(); i++)
	{
		m_RenderPath->RemoveSprite(&*m_Widgets[i]);
	}

	m_Widgets.clear();

	float differenceR = (float)(m_Data.m_End.r() - m_Data.m_Start.r()) / (float)m_Data.m_Size.y;
	float differenceG = (float)(m_Data.m_End.g() - m_Data.m_Start.g()) / (float)m_Data.m_Size.y;
	float differenceB = (float)(m_Data.m_End.b() - m_Data.m_Start.b()) / (float)m_Data.m_Size.y;

	for (float i = 0.f; i < m_Data.m_Size.y; i++)
	{
		Color color = Color(m_Data.m_Start.r() + (differenceR * i), m_Data.m_Start.g() + (differenceG * i), m_Data.m_Start.b() + (differenceB * i), m_Data.m_Start.a());
		wiSprite* gradient = new wiSprite();
		if (gradient)
		{
			m_RenderPath->AddSprite(&*gradient);
			gradient->params.color = XMFLOAT4(color.rBase(), color.gBase(), color.bBase(), color.aBase());
			gradient->params.pos = XMFLOAT3(m_Data.m_Position.x, m_Data.m_Position.y + i, 0.0f);
			gradient->params.siz = XMFLOAT2(m_Data.m_Size.x, 1);

			gradient->SetHidden(m_Data.m_Hidden);

			m_Widgets.push_back(gradient);
		}
	}
}
