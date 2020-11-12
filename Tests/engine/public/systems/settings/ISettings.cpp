/*
	File: ISettings.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "ISettings.h"

//-----------------------------------------------------------------------------
// Activates ISettings initalization process
//-----------------------------------------------------------------------------
void ISettings::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	inipp::Ini<char> ini;
	std::ifstream is("data/configs/settings.ini");
	ini.parse(is);

	inipp::extract(ini.sections["Video"]["settings.fullscreen"], m_fullscreen);
	inipp::extract(ini.sections["Video"]["settings.height"], m_height);
	inipp::extract(ini.sections["Video"]["settings.width"], m_width);
}

//-----------------------------------------------------------------------------
// Activates ISettings shutdown process
//-----------------------------------------------------------------------------
void ISettings::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of ISettings
//-----------------------------------------------------------------------------
void ISettings::Run(float dt)
{
	return;
}