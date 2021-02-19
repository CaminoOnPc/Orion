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

	int count = 16;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			//IObject* object = m_Interface->m_Tier2->m_IWorld->CreateObject("character_marvin_noai", Vector(float(i) * 4, 0, float(j) * 4), Vector(-90, 0, 0));
			//object->SetScale(Vector(1, 1, 1));
		}
	}

#if DEVELOPER
	m_Interface->m_Tier2->m_IConsole->Start(m_Interface);
#endif
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
			if (!m_Interface->m_Tier2->m_IConsole->m_Active)
			{
				m_DebugCamera->Run(dt);
			}
		}

		if (m_DebugDisplay)
		{
			m_DebugDisplay->Run(dt);
		}	

		//m_Interface->m_Tier2->m_IConsole->Run(dt);
	}
}