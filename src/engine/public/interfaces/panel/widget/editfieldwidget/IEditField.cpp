/*
	File: IEditField.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IEditField.h"

//-----------------------------------------------------------------------------
// Activates IEditField initalization process
//-----------------------------------------------------------------------------
void IEditField::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_RenderPath = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;

	m_Interface->m_Tier2->m_IWidget->m_EditFields.push_back(this);

	m_EditData.m_Color = Color(255, 255, 255, 255);
}

//-----------------------------------------------------------------------------
// Activates IEditField shutdown process
//-----------------------------------------------------------------------------
void IEditField::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IEditField
//-----------------------------------------------------------------------------
void IEditField::Run(float dt)
{
	return;
}

//-----------------------------------------------------------------------------
// Sets a widget position
//-----------------------------------------------------------------------------
void IEditField::SetPos(float x, float y, bool immedUpdate)
{
	m_Data.m_Position = Vector(x, y, 0.0f);

	if (immedUpdate)
	{
		Update();
	}
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void IEditField::GetPos(float& x, float& y)
{
	x = m_Widget->params.pos.x;
	y = m_Widget->params.pos.y;
}

//-----------------------------------------------------------------------------
// Sets a widget size
//-----------------------------------------------------------------------------
void IEditField::SetSize(float width, float height, bool immedUpdate)
{
	m_Data.m_Size = Vector(width, height, 0.0f);

	if (immedUpdate)
	{
		Update();
	}
}

//-----------------------------------------------------------------------------
// Returns a widget size
//-----------------------------------------------------------------------------
void IEditField::GetSize(float& width, float& height)
{
	height = m_Data.m_Size.y;
	width = m_Data.m_Size.x;
}

//-----------------------------------------------------------------------------
// Sets a widget visibility
//-----------------------------------------------------------------------------
void IEditField::SetHidden(bool hidden, bool immedUpdate)
{
	m_EditData.m_Hidden = hidden;
	m_Data.m_Hidden = hidden;

	if (immedUpdate)
	{
		Update();
	}
}

//-----------------------------------------------------------------------------
// Returns a widget visibility
//-----------------------------------------------------------------------------
void IEditField::GetHidden(bool& hidden)
{
	hidden = m_Data.m_Hidden;
}

//-----------------------------------------------------------------------------
// Sets a widget text
//-----------------------------------------------------------------------------
void IEditField::SetText(std::string text, bool immedUpdate)
{
	m_EditData.m_Text = text;

	if (immedUpdate)
	{
		Update();
	}
}

//-----------------------------------------------------------------------------
// Returns a widget text
//-----------------------------------------------------------------------------
void IEditField::GetText(std::string& text)
{
	text = m_EditWidget->GetTextA();
}

//-----------------------------------------------------------------------------
// Sets a widget color
//-----------------------------------------------------------------------------
void IEditField::SetColor(Color color, bool immedUpdate)
{
	m_Data.m_Color = color;

	if (immedUpdate)
	{
		Update();
	}
}

//-----------------------------------------------------------------------------
// Returns a widget position
//-----------------------------------------------------------------------------
void IEditField::GetColor(Color& color)
{
	color = m_Data.m_Color;
}

//-----------------------------------------------------------------------------
// Sets a widget font
//-----------------------------------------------------------------------------
void IEditField::SetFont(HFont* font, bool immedUpdate)
{
	m_EditData.m_Font = font;

	if (immedUpdate)
	{
		Update();
	}
}

//-----------------------------------------------------------------------------
// Returns a widget font
//-----------------------------------------------------------------------------
void IEditField::GetFont(HFont*& font)
{
	font = m_EditData.m_Font;
}

//-----------------------------------------------------------------------------
// Sets a widget event
//-----------------------------------------------------------------------------
void IEditField::SetEvent(std::function<void(const char*)> callback)
{
	m_Callback = callback;
}

//-----------------------------------------------------------------------------
// Sets a widget input
//-----------------------------------------------------------------------------
void IEditField::SetInput(const char* text)
{
	std::string value_new = m_EditData.m_Text;
	value_new.append(text);
	m_EditData.m_Text = value_new;
	m_EditWidget->SetText(m_EditData.m_Text);
}

//-----------------------------------------------------------------------------
// Sets a widget priority
//-----------------------------------------------------------------------------
void IEditField::SetPriority(int priority, bool immedUpdate)
{
	m_Data.m_Priority = priority;

	if (immedUpdate)
	{
		Update();
	}
}

//-----------------------------------------------------------------------------
// Returns a widget priority
//-----------------------------------------------------------------------------
void IEditField::GetPriority(int& priority)
{
	priority = m_Data.m_Priority;
}

//-----------------------------------------------------------------------------
// Updates a widget
//-----------------------------------------------------------------------------
void IEditField::Update(float dt)
{
	m_HitBox.pos.x = m_Data.m_Position.x;
	m_HitBox.pos.y = m_Data.m_Position.y;
	m_HitBox.siz.x = m_Data.m_Size.x;
	m_HitBox.siz.y = m_Data.m_Size.y;

	XMFLOAT4 _p = wiInput::GetPointer();
	m_PointerPosition.x = _p.x;
	m_PointerPosition.y = _p.y;
	m_PointerHitBox = Hitbox2D(m_PointerPosition, XMFLOAT2(1, 1));

	const Hitbox2D& pointerHitbox = m_PointerHitBox;
	bool intersectsPointer = pointerHitbox.intersects(m_HitBox);

	if (intersectsPointer)
	{
		if (m_Flags != IWidget::EWidgetFlags::FONTFLAGS_FOCUSED)
		{
			if ((m_Data.m_Color.r() + 15) < 255 && (m_Data.m_Color.g() + 15) < 255 && (m_Data.m_Color.b() + 15) < 255)
			{
				m_Widget->params.color = XMFLOAT4(m_Data.m_Color.rBase() + 0.025f, m_Data.m_Color.gBase() + 0.025f, m_Data.m_Color.bBase() + 0.025f, m_Data.m_Color.aBase());
			}
			else
			{
				m_Widget->params.color = XMFLOAT4(m_Data.m_Color.rBase() - 0.025f, m_Data.m_Color.gBase() - 0.025f, m_Data.m_Color.bBase() - 0.025f, m_Data.m_Color.aBase());
			}
		}

		if (wiInput::Press(wiInput::MOUSE_BUTTON_LEFT))
		{
			m_Flags = IWidget::EWidgetFlags::FONTFLAGS_FOCUSED;
		}
	}
	else
	{
		if (wiInput::Press(wiInput::MOUSE_BUTTON_LEFT))
		{
			m_Flags = IWidget::EWidgetFlags::WIDGETFLAGS_IDLE;
		}
	}

	if (m_EditWidget)
	{
		if (m_Flags && IWidget::EWidgetFlags::FONTFLAGS_FOCUSED)
		{
			m_EditData.m_Text.append(Utils::get_key());

			m_EditWidget->SetText(m_EditData.m_Text);

			if ((m_Data.m_Color.r() + 15) < 255 && (m_Data.m_Color.g() + 15) < 255 && (m_Data.m_Color.b() + 15) < 255)
			{
				m_Widget->params.color = XMFLOAT4(m_Data.m_Color.rBase() + 0.05f, m_Data.m_Color.gBase() + 0.05f, m_Data.m_Color.bBase() + 0.05f, m_Data.m_Color.aBase());
			}
			else
			{
				m_Widget->params.color = XMFLOAT4(m_Data.m_Color.rBase() - 0.05f, m_Data.m_Color.gBase() - 0.05f, m_Data.m_Color.bBase() - 0.05f, m_Data.m_Color.aBase());
			}

			if (m_Data.m_Hidden)
			{
				m_Flags = IWidget::EWidgetFlags::WIDGETFLAGS_IDLE;
			}
			
			if (wiInput::Press(wiInput::KEYBOARD_BUTTON_BACKSPACE))
			{
				if (!m_EditData.m_Text.empty())
				{
					m_EditData.m_Text.pop_back();
				}

				m_EditWidget->SetText(m_EditData.m_Text);
			}	
			else if (wiInput::Press(wiInput::KEYBOARD_BUTTON_ENTER))
			{
				m_Callback(m_EditData.m_Text.c_str());

				m_EditData.m_Text.clear();
				m_EditWidget->SetText(m_EditData.m_Text);
			}
			else if (wiInput::Press(wiInput::KEYBOARD_BUTTON_ESCAPE))
			{
				m_Flags = IWidget::EWidgetFlags::WIDGETFLAGS_IDLE;
			}
		}
		else
		{
			if (!intersectsPointer)
			{
				m_Widget->params.color = XMFLOAT4(m_Data.m_Color.rBase(), m_Data.m_Color.gBase(), m_Data.m_Color.bBase(), m_Data.m_Color.aBase());
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Updates a widget
//-----------------------------------------------------------------------------
void IEditField::Update()
{
	m_RenderPath->RemoveSprite(m_Widget);

	m_Widget = new wiSprite();
	m_RenderPath->AddSprite(&*m_Widget);

	m_RenderPath->SetSpriteOrder(m_Widget, m_Data.m_Priority);

	m_Widget->params.color = XMFLOAT4(m_Data.m_Color.rBase(), m_Data.m_Color.gBase(), m_Data.m_Color.bBase(), m_Data.m_Color.aBase());

	m_Widget->params.pos = XMFLOAT3(m_Data.m_Position.x, m_Data.m_Position.y, 0.0f);
	m_Widget->params.siz = XMFLOAT2(m_Data.m_Size.x, m_Data.m_Size.y);

	m_Widget->SetHidden(m_Data.m_Hidden);

	m_RenderPath->RemoveFont(m_EditWidget);

	m_EditWidget = new wiSpriteFont();
	m_RenderPath->AddFont(&*m_EditWidget);

	m_RenderPath->SetFontOrder(m_EditWidget, m_Data.m_Priority);

	if (!m_EditData.m_Text.empty())
	{
		m_EditWidget->SetText(m_EditData.m_Text);
	}

	if (m_EditData.m_Font)
	{
		m_EditWidget->params.style = m_EditData.m_Font->m_Font.m_Style;
		m_EditWidget->params.size = m_EditData.m_Font->m_Font.m_Size;

		if (m_EditData.m_Font->m_Font.m_Flag && IWidget::EFontFlags::FONTFLAGS_OUTLINE)
		{
			m_EditWidget->params.outlineColor = wiColor::Black();
		}

		if (m_EditData.m_Font->m_Font.m_Flag && IWidget::EFontFlags::FONTFLAGS_SHADOW)
		{
			m_EditWidget->params.shadowColor = wiColor::Black();
		}
	}

	if (m_EditData.m_Size > 0)
	{
		m_EditWidget->params.size = m_EditData.m_Size;
	}

	m_EditWidget->params.color = wiColor(m_EditData.m_Color.r(), m_EditData.m_Color.g(), m_EditData.m_Color.b(), m_EditData.m_Color.a());
	m_EditWidget->params.posX = m_Data.m_Position.x + 5;
	m_EditWidget->params.posY = m_Data.m_Position.y + (m_Data.m_Size.y / 6);

	m_EditWidget->SetHidden(m_EditData.m_Hidden);
}
