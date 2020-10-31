/*
	File: IInterfaces.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IInterfaces.h"

#include "..\..\common\WinMain.h"

bool IInterfaces::EOnInit(IBase* base)
{
	m_Base = base;

	// Tiers
	m_Tier0 = new Tier0;
	if (!m_Tier0)
	{
		return false;
	}

	m_Tier0->Start(this);

	m_Tier1 = new Tier1;
	if (!m_Tier1)
	{
		return false;
	}

	m_Tier1->Start(this);

	m_Tier2 = new Tier2;
	if (!m_Tier2)
	{
		return false;
	}

	m_Tier2->Start(this);

	m_Tier3 = new Tier3;
	if (!m_Tier3)
	{
		return false;
	}

	m_Tier3->Start(this);

	return true;
}

bool IInterfaces::EOnFinish()
{
	// Tiers
	m_Tier0->Stop();
	SafeRelease(&m_Tier0);

	m_Tier1->Stop();
	SafeRelease(&m_Tier1);

	m_Tier2->Stop();
	SafeRelease(&m_Tier2);

	m_Tier3->Stop();
	SafeRelease(&m_Tier3);

	return true;
}

bool IInterfaces::EOnFrame()
{
	// Tiers
	m_Tier0->Run();
	m_Tier1->Run();
	m_Tier2->Run();
	m_Tier3->Run();

	return true;
}

bool IInterfaces::EOnUpdate()
{
	if (!EOnFrame())
	{
		return false;
	}

	return true;
}