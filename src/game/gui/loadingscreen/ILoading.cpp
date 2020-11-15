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

	m_Loading = new IImageWidget;
	m_Loading->Start(m_Interface);

	m_Loading->SetImage("data/game/materials/textures/loadscreen/loading_1.png");

	m_Loading->SetPos(0, 0);
	m_Loading->SetSize(wiRenderer::GetDevice()->GetScreenWidth(), wiRenderer::GetDevice()->GetScreenHeight());

	LoadingScreen::Load();
}

//-----------------------------------------------------------------------------
// Processing a single frame of ILoading
//-----------------------------------------------------------------------------
void ILoading::Update(float dt)
{
	LoadingScreen::Update(dt);
}