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

	m_Interface->m_Tier2->m_IWorld->CreateWorld("data/game/worlds/world_empty.wiscene");

	int count = 32;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			IObject* object = m_Interface->m_Tier2->m_IWorld->CreateObject("character_marvin_noai", Vector(float(i) * 4, 0, float(j) * 4), Vector(-90, 0, 0));
			object->SetScale(Vector(1, 1, 1));
		}
	}

	//IObject* object = m_Interface->m_Tier2->m_IWorld->CreateObject("zuccini", Vector(float(0) * 4, 0, float(0) * 4), Vector(0, 0, 0));
	//object->SetScale(Vector(100, 100, 100));

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

	/*
	* TODO@: 
	* Lod support
	* Support for relative paths that go backwards in editor 
	* 
	* Console
	* Rework surface interface to behave more like a widget
	* Pottentially add Direct2D back and use it as a widget instead of dynamic panel to save fps (TODO@: Test in Orion V1.0 if that will actually help with fps)
	* 
	* Add scripting language support - squirrel
	* Add archieve system to store assets in them rather than trying to access files dirrectly
	*/
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