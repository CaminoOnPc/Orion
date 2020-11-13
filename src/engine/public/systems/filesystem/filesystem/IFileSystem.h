/*
	File: IFileSystem.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../HObject.h"

class HObject;

class IInterfaces;

class IFileSystem
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates IFileSystem initalization process
	void Start(IInterfaces* interfaces);

	// Activates IFileSystem shutdown process
	void Stop();

	// Processing a single frame of IFileSystem
	void Run(float dt);

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
	std::vector< HObject* > m_Objects;
};