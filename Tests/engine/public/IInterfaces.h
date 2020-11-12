/*
	File: IInterfaces.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include "../public/IBase.h"

#include "../../engine/tiers/tier0/Tier0.h"
#include "../../engine/tiers/tier1/Tier1.h"
#include "../../engine/tiers/tier2/Tier2.h"
#include "../../engine/tiers/tier3/Tier3.h"

class IBase;

class Tier0;
class Tier1;
class Tier2;
class Tier3;

class IInterfaces
{
public:
	// * Those are tier1 calls allocated for class initialization and running
	// ---------------------------------------------

	bool EOnInit(IBase* base);
	bool EOnFinish();

	bool EOnFrame(float dt);
	bool EOnUpdate(float dt);

protected:
	template <class T> void SafeRelease(T** ppT)
	{
		if (*ppT)
		{
			*ppT = nullptr;
		}
	}
public:
	IBase* m_Base;
public:
	Tier0* m_Tier0;
	Tier1* m_Tier1;
	Tier2* m_Tier2;
	Tier3* m_Tier3;
public:
	HINSTANCE m_HInstance;
};