/*
	File: Tier2.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "Tier2.h"

void Tier2::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_IFileSystem = new IFileSystem;
	if (!m_IFileSystem)
	{
		return;
	}

	m_IFileSystem->Start(m_Interface);

	m_IWidget = new IWidget;
	if (!m_IWidget)
	{
		return;
	}

	m_IWidget->Start(m_Interface);

	m_IWorld = new IWorld;
	if (!m_IWorld)
	{
		return;
	}

	m_IWorld->Start(m_Interface);

	m_IConsole = new IConsole;
	if (!m_IConsole)
	{
		return;
	}

	//m_IConsole->Start(m_Interface);

	return;
}

void Tier2::Stop()
{
	SafeRelease(&m_Interface);

	return;
}

void Tier2::Run(float dt)
{
	m_IWorld->Run(dt);

	return;
}
