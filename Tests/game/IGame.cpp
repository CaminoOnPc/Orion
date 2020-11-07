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

	//wiProfiler::SetEnabled(true);
	
	wiRenderer::ClearWorld();
	wiScene::GetScene().weather = wiScene::WeatherComponent();

	

	const float scale = 0.05f;
	int count = 16;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			//m_Interface->m_Tier2->m_IWorld->CreateObject("marvin", "", Vector(float(i) * 6, 0, float(j) * 6), Vector(90, 0, 0));
		}
	}

	m_Interface->m_Tier2->m_IWorld->CreateObject("marvin", "", Vector(0, 0, 0), Vector(90, 0, 0));
	m_Interface->m_Tier2->m_IWorld->CreateObject("marvin", "", Vector(10, 0, 0), Vector(90, 0, 0));
	m_Interface->m_Tier2->m_IWorld->CreateObject("marvin", "", Vector(10, 0, 0), Vector(90, 0, 0));

	auto& weather = wiScene::GetScene().weathers.Create(wiECS::CreateEntity());
	weather.ambient = XMFLOAT3(0.2f, 0.2f, 0.2f);
	weather.horizon = XMFLOAT3(0.38f, 0.38f, 0.38f);
	weather.zenith = XMFLOAT3(0.42f, 0.42f, 0.42f);
	weather.cloudiness = 0.0f;
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