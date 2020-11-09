/*
	File: IGame.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IGame.h"

//-----------------------------------------------------------------------------
// Activates IGame initalization process
//-----------------------------------------------------------------------------
void IGame::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_DebugCamera = new IDebugCamera;
	if (!m_DebugCamera)
	{
		return;
	}

	m_DebugCamera->Start(m_Interface);

	m_DebugDisplay = new IDebugDisplay;
	if (!m_DebugDisplay)
	{
		return;
	}

	m_DebugDisplay->Start(m_Interface);

	m_Interface->m_Tier2->m_IWorld->CreateWorld("data/game/worlds/world_empty.ent");

	int count = 32;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			m_Interface->m_Tier2->m_IWorld->CreateObject("character_marvin_noai", Vector(float(i) * 6, 0, float(j) * 6), Vector(-90, 0, 0));
		}
	}

	m_UI = wiSprite("data/game/materials/textures/ui/ui.png");
	m_UI.params.sampleFlag = SAMPLEMODE_CLAMP;
	m_UI.params.blendFlag = BLENDMODE_ALPHA;
	m_UI.params.quality = QUALITY_LINEAR;
	m_UI.params.pos = XMFLOAT3(0, 0, 0.0f);
	m_UI.params.enableFullScreen();

	RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	path->AddSprite(&m_UI);

	ISound* music = m_Interface->m_Tier2->m_IWorld->CreateSoundObject2D("data/game/sounds/sound_music_ambient_1.ogg");
	music->SetVolume(0.1f);
}

//-----------------------------------------------------------------------------
// Activates IGame shutdown process
//-----------------------------------------------------------------------------
void IGame::Stop()
{
}

//-----------------------------------------------------------------------------
// Processing a single frame of IGame
//-----------------------------------------------------------------------------
void IGame::Run(float dt)
{
	if (m_Interface)
	{
		if (m_DebugCamera)
		{
			m_DebugCamera->Run(dt);
		}

		if (m_DebugDisplay)
		{
			m_DebugDisplay->Run(dt);
		}	
	}
}