/*
	File: ILoading.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "ILoading.h"

//-----------------------------------------------------------------------------
// Activates IRendering initalization process
//-----------------------------------------------------------------------------
void ILoading::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	Load();
}

//-----------------------------------------------------------------------------
// Activates ILoading initalization process
//-----------------------------------------------------------------------------
void ILoading::Load()
{
	m_Interface->m_Tier0->m_Rendering->m_RenderPath = this;

	m_Interface->m_Tier2->m_ISurface->StartFrame();

	m_Interface->m_Tier2->m_ISurface->DrawBitmap("data/game/gui/images/loading_1.png", 0, 0, wiRenderer::GetDevice()->GetScreenWidth(), wiRenderer::GetDevice()->GetScreenHeight(), 255);

	//static HFont* font = m_Interface->m_Tier2->m_ISurface->CreateFont("Arial", 16, ISurface::EFontFlags::FONTFLAGS_OUTLINE);
	//std::string version;
	//version.append("Orion ");
	//version.append(wiVersion::GetVersionString());
	//m_Interface->m_Tier2->m_ISurface->DrawText(font, version.c_str(), 10, 10, Color(255, 255, 255));

	LoadingScreen::Load();
}

//-----------------------------------------------------------------------------
// Processing a single frame of ILoading
//-----------------------------------------------------------------------------
void ILoading::Update(float dt)
{
	LoadingScreen::Update(dt);
}