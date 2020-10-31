/*
	File: IRendering.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class IWickedRenderer : public RenderPath3D
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates IWickedRenderer initalization process
	void Start(IInterfaces* interfaces);

	// Activates IWickedRenderer shutdown process
	void Stop();

	// Processing a single frame of IWickedRenderer
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
};

class IWicked : public MainComponent
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates IWicked initalization process
	void Start(IInterfaces* interfaces);

	// Activates IWicked shutdown process
	void Stop();

	// Processing a single frame of IWicked
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
	IWickedRenderer* m_Renderer;
};