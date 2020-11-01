/*
	File: IRendering.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "IWicked.h"

class IWicked;

class IInterfaces;

class IRendering
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates IRendering initalization process
	void Start(IInterfaces* interfaces);

	// Activates IRendering shutdown process
	void Stop();

	// Processing a single frame of IRendering
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
	IWicked* m_Wicked;
public:
	RenderPath* m_RenderPath;
};