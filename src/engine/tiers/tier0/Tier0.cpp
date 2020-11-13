/*
	File: Tier0.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "Tier0.h"

void Tier0::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_Rendering = new IRendering;
	if (!m_Rendering)
	{
		return;
	}

	m_Rendering->Start(m_Interface);

	return;
}

void Tier0::Stop()
{
	SafeRelease(&m_Interface);

	return;
}

void Tier0::Run(float dt)
{
	m_Rendering->Run(dt);

	return;
}
