/*
	File: Tier2.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../../public/interfaces/panel/surface/ISurface.h"

class ISurface;

class IInterfaces;

class Tier2
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates Tier2 initialization process
	void Start(IInterfaces* interfaces);

	// Activates Tier2 shutdown process
	void Stop();

	// Processing a single frame of Tier2
	void Run();

protected:
	IInterfaces* m_Interface;
protected:
	template <class T> void SafeRelease(T** ppT)
	{
		if (*ppT)
		{
			*ppT = nullptr;
		}
	}
public:
	ISurface* m_ISurface;
};