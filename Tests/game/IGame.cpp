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

	m_Camera = new IDebugCamera;
	if (!m_Camera)
	{
		return;
	}

	m_Camera->Start(m_Interface);

	//wiRenderer::SetTemporalAAEnabled(true);
	//wiScene::LoadModel("data/game/worlds/sponza.wiscene");

	m_Interface->m_Tier2->m_IWorld->CreateObject("test", "", Vector(0, 5, 0), Vector(0, 0, 0));
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
		if (m_Camera)
		{
			m_Camera->Run(dt);
		}
	}
}