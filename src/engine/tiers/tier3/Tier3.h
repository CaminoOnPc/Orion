/*
	File: Tier3.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../../../game/IGame.h"

class IGame;

class IInterfaces;

class Tier3
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates Tier3 initialization process
	void Start(IInterfaces* interfaces);

	// Activates Tier3 shutdown process
	void Stop();

	// Processing a single frame of Tier3
	void Run(float dt);

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
	IGame* m_IGame;
};