/*
	File: IRendering.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../loadingscreen/ILoading.h"

class ILoading;

class IInterfaces;

class IWickedRenderer : public RenderPath3D
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	// Activates IWicked initalization process
	void Start(IInterfaces* interfaces);

	// Activates IWickedRenderer loading process
	void Load() override;

	// Updating a single frame of IWickedRenderer
	void Update(float dt) override;

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

	// Activates IWicked loading process
	void Initialize() override;

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
public:
	ILoading* m_Loading;
};