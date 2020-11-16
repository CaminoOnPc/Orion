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

	Update();
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

	Update();
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

	Update();
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

	Update();
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

	Update();
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

	Update();
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
			if (m_Data.m_Hidden)
			{
				m_Flags = IWidget::EWidgetFlags::WIDGETFLAGS_IDLE;
			}

			if (wiInput::Press((wiInput::BUTTON)'A'))
			{
				m_EditData.m_Text.append("a");
			}
			else if (wiInput::Press((wiInput::BUTTON)'B'))
			{
				m_EditData.m_Text.append("b");
			}
			else if (wiInput::Press((wiInput::BUTTON)'C'))
			{
				m_EditData.m_Text.append("c");
			}
			else if (wiInput::Press((wiInput::BUTTON)'D'))
			{
				m_EditData.m_Text.append("d");
			}
			else if (wiInput::Press((wiInput::BUTTON)'E'))
			{
				m_EditData.m_Text.append("e");
			}
			else if (wiInput::Press((wiInput::BUTTON)'F'))
			{
				m_EditData.m_Text.append("f");
			}
			else if (wiInput::Press((wiInput::BUTTON)'G'))
			{
				m_EditData.m_Text.append("g");
			}
			else if (wiInput::Press((wiInput::BUTTON)'H'))
			{
				m_EditData.m_Text.append("h");
			}
			else if (wiInput::Press((wiInput::BUTTON)'I'))
			{
				m_EditData.m_Text.append("i");
			}
			else if (wiInput::Press((wiInput::BUTTON)'J'))
			{
				m_EditData.m_Text.append("j");
			}
			else if (wiInput::Press((wiInput::BUTTON)'K'))
			{
				m_EditData.m_Text.append("k");
			}
			else if (wiInput::Press((wiInput::BUTTON)'L'))
			{
				m_EditData.m_Text.append("l");
			}
			else if (wiInput::Press((wiInput::BUTTON)'M'))
			{
				m_EditData.m_Text.append("m");
			}
			else if (wiInput::Press((wiInput::BUTTON)'N'))
			{
				m_EditData.m_Text.append("n");
			}
			else if (wiInput::Press((wiInput::BUTTON)'O'))
			{
				m_EditData.m_Text.append("o");
			}
			else if (wiInput::Press((wiInput::BUTTON)'P'))
			{
				m_EditData.m_Text.append("p");
			}
			else if (wiInput::Press((wiInput::BUTTON)'Q'))
			{
				m_EditData.m_Text.append("q");
			}
			else if (wiInput::Press((wiInput::BUTTON)'R'))
			{
				m_EditData.m_Text.append("r");
			}
			else if (wiInput::Press((wiInput::BUTTON)'S'))
			{
				m_EditData.m_Text.append("s");
			}
			else if (wiInput::Press((wiInput::BUTTON)'T'))
			{
				m_EditData.m_Text.append("t");
			}
			else if (wiInput::Press((wiInput::BUTTON)'U'))
			{
				m_EditData.m_Text.append("u");
			}
			else if (wiInput::Press((wiInput::BUTTON)'V'))
			{
				m_EditData.m_Text.append("v");
			}
			else if (wiInput::Press((wiInput::BUTTON)'W'))
			{
				m_EditData.m_Text.append("w");
			}
			else if (wiInput::Press((wiInput::BUTTON)'X'))
			{
				m_EditData.m_Text.append("x");
			}
			else if (wiInput::Press((wiInput::BUTTON)'Y'))
			{
				m_EditData.m_Text.append("y");
			}
			else if (wiInput::Press((wiInput::BUTTON)'Z'))
			{
				m_EditData.m_Text.append("z");
			}

			if (wiInput::Down(wiInput::BUTTON::KEYBOARD_BUTTON_LSHIFT) || wiInput::Down(wiInput::BUTTON::KEYBOARD_BUTTON_RSHIFT))
			{
				if (wiInput::Press((wiInput::BUTTON)VK_OEM_MINUS))
				{
					m_EditData.m_Text.append("_");
				}
			}

			if (wiInput::Press(wiInput::BUTTON::KEYBOARD_BUTTON_SPACE))
			{
				m_EditData.m_Text.append(" ");
			}

			if (wiInput::Press((wiInput::BUTTON)'1'))
			{
				m_EditData.m_Text.append("1");
			}
			else if (wiInput::Press((wiInput::BUTTON)'2'))
			{
				m_EditData.m_Text.append("2");
			}
			else if (wiInput::Press((wiInput::BUTTON)'3'))
			{
				m_EditData.m_Text.append("3");
			}
			else if (wiInput::Press((wiInput::BUTTON)'4'))
			{
				m_EditData.m_Text.append("4");
			}
			else if (wiInput::Press((wiInput::BUTTON)'5'))
			{
				m_EditData.m_Text.append("5");
			}
			else if (wiInput::Press((wiInput::BUTTON)'6'))
			{
				m_EditData.m_Text.append("6");
			}
			else if (wiInput::Press((wiInput::BUTTON)'7'))
			{
				m_EditData.m_Text.append("7");
			}
			else if (wiInput::Press((wiInput::BUTTON)'8'))
			{
				m_EditData.m_Text.append("8");
			}
			else if (wiInput::Press((wiInput::BUTTON)'9'))
			{
				m_EditData.m_Text.append("9");
			}
			else if (wiInput::Press((wiInput::BUTTON)'0'))
			{
				m_EditData.m_Text.append("0");
			}

			if (wiInput::Press((wiInput::BUTTON)VK_OEM_PERIOD))
			{
				m_EditData.m_Text.append(".");
			}

			m_EditWidget->SetText(m_EditData.m_Text);

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

	m_Widget->params.color = XMFLOAT4(m_Data.m_Color.rBase(), m_Data.m_Color.gBase(), m_Data.m_Color.bBase(), m_Data.m_Color.aBase());

	m_Widget->params.pos = XMFLOAT3(m_Data.m_Position.x, m_Data.m_Position.y, 0.0f);
	m_Widget->params.siz = XMFLOAT2(m_Data.m_Size.x, m_Data.m_Size.y);

	m_Widget->SetHidden(m_Data.m_Hidden);

	m_RenderPath->RemoveFont(m_EditWidget);

	m_EditWidget = new wiSpriteFont();
	m_RenderPath->AddFont(&*m_EditWidget);

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
