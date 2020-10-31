/*
	File: IBase.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../public/systems/settings/ISettings.h"

class ISettings;

class IInterfaces;

class IBase : public MainComponent
{
public:
	// * Those are calls allocated for class initialization and running
	// ---------------------------------------------

	bool EOnInit(HINSTANCE instance);
	bool EOnFinish();

	void EOnFrame();
	void EOnUpdate();
public:
	IInterfaces* m_Interfaces;
protected:
	template <class T> void SafeRelease(T** ppT)
	{
		if (*ppT)
		{
			*ppT = nullptr;
		}
	}
public:
	ISettings* m_Settings;
}; static IBase* m_Base;

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);