/*
	File: IHelicopter.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IHelicopter.h"

//-----------------------------------------------------------------------------
// Activates IHelicopter initalization process
//-----------------------------------------------------------------------------
void IHelicopter::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IHelicopter shutdown process
//-----------------------------------------------------------------------------
void IHelicopter::Stop()
{
	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of IHelicopter
//-----------------------------------------------------------------------------
void IHelicopter::Run(float dt)
{
	
}