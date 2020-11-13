/*
	File: HCvar.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "HCvar.h"

//-----------------------------------------------------------------------------
// Creates HCvar font handle
//-----------------------------------------------------------------------------
HCvar::HCvar(const char* command)
{
	m_Cvar.m_Command = command;
}

//-----------------------------------------------------------------------------
// Destroys HCvar font handle
//-----------------------------------------------------------------------------
HCvar::~HCvar()
{
}