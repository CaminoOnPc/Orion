/*
	File: IConsole.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IConsole.h"

//-----------------------------------------------------------------------------
// Activates ICamera initalization process
//-----------------------------------------------------------------------------
void IConsole::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	r_vsync = new HCvar("r_vsync");
	r_vsync->m_Cvar.m_IntValue = 0;
	m_Cvars.push_back(r_vsync);
}

//-----------------------------------------------------------------------------
// Activates IConsole shutdown process
//-----------------------------------------------------------------------------
void IConsole::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IConsole
//-----------------------------------------------------------------------------
void IConsole::Run(float dt)
{
}

//-----------------------------------------------------------------------------
// Executes a given command
//-----------------------------------------------------------------------------
void IConsole::ExecuteCommand(const char* command, const char* args)
{
	InternalExecuteCommand(command, args, 0, 0);
}

//-----------------------------------------------------------------------------
// Executes a given command
//-----------------------------------------------------------------------------
void IConsole::ExecuteCommand(const char* command, float args)
{
	InternalExecuteCommand(command, std::to_string(args).c_str(), args, args);
}

//-----------------------------------------------------------------------------
// Executes a given command
//-----------------------------------------------------------------------------
void IConsole::ExecuteCommand(const char* command, int args)
{
	InternalExecuteCommand(command, std::to_string(args).c_str(), args, args);
}

//-----------------------------------------------------------------------------
// Executes a given command
//-----------------------------------------------------------------------------
void IConsole::InternalExecuteCommand(const char* command, const char* args, float fargs, int iargs)
{
	if (command == "r_vsync")
	{
		Callback_r_vsync(iargs);
	}
}

//-----------------------------------------------------------------------------
// Callbacks for given commands
//-----------------------------------------------------------------------------
void IConsole::Callback_r_vsync(int value)
{
	if (value > 0)
	{
		wiRenderer::GetDevice()->SetVSyncEnabled(true);
	}
	else
	{
		wiRenderer::GetDevice()->SetVSyncEnabled(false);
	}
}
