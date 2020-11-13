/*
	File: IWicked.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IWicked.h"

//-----------------------------------------------------------------------------
// Activates IRendering initalization process
//-----------------------------------------------------------------------------
void IWicked::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IWicked initalization process
//-----------------------------------------------------------------------------
void IWicked::Initialize()
{
	wiFont::SetFontPath(Utils::get_font_directory());
	wiRenderer::SetShaderPath("data/engine/shadercache/");

	MainComponent::Initialize();

	m_Loading = new ILoading;
	if (!m_Loading)
	{
		return;
	}

	m_Loading->Start(m_Interface);

	m_Renderer = new IWickedRenderer;
	if (!m_Renderer)
	{
		return;
	}

	m_Renderer->Start(m_Interface);

	m_Loading->addLoadingComponent(&*m_Renderer, this, 0.2f);
	ActivatePath(&*m_Loading, 0.2f);
	m_Loading->onFinished([&] 
	{
		ActivatePath(&*m_Renderer);
	});
}

//-----------------------------------------------------------------------------
// Activates IRendering initalization process
//-----------------------------------------------------------------------------
void IWickedRenderer::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IWickedRenderer initalization process
//-----------------------------------------------------------------------------
void IWickedRenderer::Load()
{
	// Demonstrates that loading screen is working
	Sleep(1000);

	wiRenderer::GetDevice()->SetVSyncEnabled(false);

	m_Interface->m_Tier0->m_Rendering->m_RenderPath = this;

	m_Interface->m_Tier3->m_IGame->Start(m_Interface);

	RenderPath3D::Load();
}

//-----------------------------------------------------------------------------
// Processing a single frame of IWickedRenderer
//-----------------------------------------------------------------------------
void IWickedRenderer::Update(float dt)
{
	if (m_Interface->m_Tier3->m_IGame)
	{
		m_Interface->m_Tier3->m_IGame->Run(dt);
	}

	RenderPath3D::Update(dt);
}
