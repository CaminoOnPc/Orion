/*
	File: Tier2.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "Tier2.h"

void Tier2::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_ISurface = new ISurface;
	if (!m_ISurface)
	{
		return;
	}

	m_ISurface->Start(m_Interface);

	return;
}

void Tier2::Stop()
{
	SafeRelease(&m_Interface);

	return;
}

void Tier2::Run()
{
	return;
}
