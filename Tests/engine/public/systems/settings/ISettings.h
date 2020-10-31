/*
	File: ISettings.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include <inipp.h>

class IInterfaces;

class ISettings
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates ISettings initalization process
	void Start(IInterfaces* interfaces);

	// Activates ISettings shutdown process
	void Stop();

	// Processing a single frame of ISettings
	void Run();

	// * Those are calls that are accessible by everyone 
	// ---------------------------------------------

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
	int m_fullscreen;
	int m_height;
	int m_width;
};