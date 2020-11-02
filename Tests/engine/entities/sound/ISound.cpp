/*
	File: ISound.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "ISound.h"

//-----------------------------------------------------------------------------
// Activates ISound initalization process
//-----------------------------------------------------------------------------
void ISound::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates ISound shutdown process
//-----------------------------------------------------------------------------
void ISound::Stop()
{
	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of ISound
//-----------------------------------------------------------------------------
void ISound::Run()
{

}

//-----------------------------------------------------------------------------
// Sets an audio position
//-----------------------------------------------------------------------------
void ISound::SetPosition(Vector position)
{
	m_Position = position;
}

//-----------------------------------------------------------------------------
// Returns an audio position
//-----------------------------------------------------------------------------
Vector ISound::GetPosition()
{
	return m_Position;
}