/*
	File: Tier2.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../../public/interfaces/console/console/IConsole.h"
#include "../../public/systems/filesystem/filesystem/IFileSystem.h"
#include "../../public/interfaces/world/IWorld.h"

class IFileSystem;
class IConsole;
class IWidget;
class IWorld;

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
	IFileSystem* m_IFileSystem;
	IConsole* m_IConsole;
	IWidget* m_IWidget;
	IWorld* m_IWorld;
};