/*
	File: Tier1.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class Tier1
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates Tier1 initialization process
	void Start(IInterfaces* interfaces);

	// Activates Tier1 shutdown process
	void Stop();

	// Processing a single frame of Tier1
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
};