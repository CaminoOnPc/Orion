/*
	File: IRendering.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IRendering.h"

//-----------------------------------------------------------------------------
// Activates IRendering initalization process
//-----------------------------------------------------------------------------
void IRendering::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_Wicked = new IWicked;
	if (!m_Wicked)
	{
		return;
	}
}

//-----------------------------------------------------------------------------
// Activates IRendering shutdown process
//-----------------------------------------------------------------------------
void IRendering::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IRendering
//-----------------------------------------------------------------------------
void IRendering::Run()
{
	m_Wicked->Run();
}