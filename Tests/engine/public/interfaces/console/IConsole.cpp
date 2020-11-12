/*
	File: IConsole.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IConsole.h"

//-----------------------------------------------------------------------------
// Activates ICamera initalization process
//-----------------------------------------------------------------------------
void IConsole::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IConsole shutdown process
//-----------------------------------------------------------------------------
void IConsole::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IConsole
//-----------------------------------------------------------------------------
void IConsole::Run(float dt)
{
}