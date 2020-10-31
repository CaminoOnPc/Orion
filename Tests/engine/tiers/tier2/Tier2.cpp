/*
	File: Tier2.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "Tier2.h"

void Tier2::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	return;
}

void Tier2::Stop()
{
	SafeRelease(&m_Interface);

	return;
}

void Tier2::Run()
{
	return;
}
