/*
	File: Tier1.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "Tier1.h"

void Tier1::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	return;
}

void Tier1::Stop()
{
	SafeRelease(&m_Interface);

	return;
}

void Tier1::Run(float dt)
{
	return;
}
