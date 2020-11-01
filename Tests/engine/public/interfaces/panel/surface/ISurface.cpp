/*
	File: ISurface.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "ISurface.h"

//-----------------------------------------------------------------------------
// Activates ISurface initalization process
//-----------------------------------------------------------------------------
void ISurface::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates ISurface shutdown process
//-----------------------------------------------------------------------------
void ISurface::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of ISurface
//-----------------------------------------------------------------------------
void ISurface::Run()
{
	return;
}

//-----------------------------------------------------------------------------
// End processing of a single frame
//-----------------------------------------------------------------------------
void ISurface::StartFrame()
{
	
}

//-----------------------------------------------------------------------------
// End processing of a single frame
//-----------------------------------------------------------------------------
void ISurface::EndFrame()
{
	
}

//-----------------------------------------------------------------------------
// Sets font and flags of the text
//-----------------------------------------------------------------------------
HFont* ISurface::CreateFont(const char* font, int size, int flags)
{
	return new HFont(font, size, flags);
}

//-----------------------------------------------------------------------------
// Draw text
//-----------------------------------------------------------------------------
void ISurface::DrawText(HFont* font, const char* text, int x, int y, Color color)
{
	if (!font->m_Font.m_Flag)
	{
		static wiSpriteFont textSprite;
		textSprite = wiSpriteFont(
			text,
			wiFontParams(
			x,
			y,
			font->m_Font.m_Size,
			WIFALIGN_LEFT,
			WIFALIGN_LEFT));

		RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
		path->AddFont(&textSprite);
	};

	if (font->m_Font.m_Flag && FONTFLAGS_OUTLINE)
	{
		DrawText(font, text, x, y, 1, Color(0, 0, 0, 255));
		DrawText(font, text, x - 1, y, 1, Color(0, 0, 0, 255));
		DrawText(font, text, x, y - 1, 1, Color(0, 0, 0, 255));
		DrawText(font, text, x + 1, y, 1, Color(0, 0, 0, 255));
		DrawText(font, text, x, y + 1, 1, Color(0, 0, 0, 255));

		DrawText(font, text, x, y, 0, color);
	}
}

//-----------------------------------------------------------------------------
// Draw text with custom flags
//-----------------------------------------------------------------------------
void ISurface::DrawText(HFont* font, const char* text, int x, int y, int flags, Color color)
{
	static wiSpriteFont textSprite;
	textSprite = wiSpriteFont(
		text,
		wiFontParams(
			x,
			y,
			font->m_Font.m_Size,
			WIFALIGN_CENTER,
			WIFALIGN_CENTER));

	RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	path->AddFont(&textSprite);
}

//-----------------------------------------------------------------------------
// Draw rectangle
//-----------------------------------------------------------------------------
void ISurface::DrawRect(int x, int y, float w, float h, Color color)
{
	static wiSprite rectSprite;
	rectSprite.params.pos = XMFLOAT3(x, y, 0.0f);
	rectSprite.params.siz = XMFLOAT2(w, h);
	rectSprite.params.pivot = XMFLOAT2(0.5f, 0.5f);
	rectSprite.params.color = XMFLOAT4(color.rBase(), color.gBase(), color.bBase(), color.aBase());

	RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	path->AddSprite(&rectSprite);
}

//-----------------------------------------------------------------------------
// Draw rectangle with outline
//-----------------------------------------------------------------------------
void ISurface::DrawRect(int x, int y, float w, float h, bool outline, Color color)
{
	static wiSprite rectSprite;
	rectSprite.params.pos = XMFLOAT3(x, y, 0.0f);
	rectSprite.params.siz = XMFLOAT2(w, h);
	rectSprite.params.pivot = XMFLOAT2(0.5f, 0.5f);
	rectSprite.params.color = XMFLOAT4(color.rBase(), color.gBase(), color.bBase(), color.aBase());

	RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	path->AddSprite(&rectSprite);

	if (outline)
	{
		static wiSprite rectSpriteOutline;
		rectSpriteOutline.params.pos = XMFLOAT3(x - 1, y - 1, 0.0f);
		rectSpriteOutline.params.siz = XMFLOAT2(w + 1, h + 1);
		rectSpriteOutline.params.pivot = XMFLOAT2(0.5f, 0.5f);
		rectSpriteOutline.params.color = XMFLOAT4(0.0f, 0.0f, 0.0f, color.aBase());
		
		RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
		path->AddSprite(&rectSprite);
	}
}

//-----------------------------------------------------------------------------
// Draw line
//-----------------------------------------------------------------------------
void ISurface::DrawLine(int x0, int y0, int x1, int y1, Color color)
{

}

//-----------------------------------------------------------------------------
// Draw line with custom width
//-----------------------------------------------------------------------------
void ISurface::DrawLine(int x0, int y0, int x1, int y1, float width, Color color)
{

}

//-----------------------------------------------------------------------------
// Draw bitmap image
//-----------------------------------------------------------------------------
void ISurface::DrawBitmap(const char* image, int x, int y, float w, float h, float alpha)
{
	static wiSprite imageSprite;
	imageSprite = wiSprite(image);
	imageSprite.params.pos = XMFLOAT3(x, y, 0.0f);
	imageSprite.params.siz = XMFLOAT2(1024, 512);
	imageSprite.params.opacity = alpha / 255;
	imageSprite.params.enableFullScreen();

	RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	path->AddSprite(&imageSprite);
}
