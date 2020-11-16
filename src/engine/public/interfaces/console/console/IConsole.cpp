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

	mat_vsync = new HCvar("mat_vsync");
	mat_vsync->m_Cvar.m_IntValue = 0;
	m_Cvars.push_back(mat_vsync);

	mat_mode = new HCvar("mat_mode");
	mat_mode->m_Cvar.m_IntValue = 0;
	m_Cvars.push_back(mat_mode);

	clear = new HCvar("clear");
	m_Cvars.push_back(clear);

	quit = new HCvar("quit");
	m_Cvars.push_back(quit);

	m_HeaderWidget = new IGradientWidget;
	m_HeaderWidget->Start(m_Interface);

	m_HeaderWidget->SetColor(Color(55, 55, 55, 225), Color(15, 15, 15, 225));

	m_HeaderWidget->SetPos(10, 10);
	m_HeaderWidget->SetSize(m_Interface->m_Base->m_Settings->m_width - 20, 25);

	m_BackgroundWidget = new IGradientWidget;
	m_BackgroundWidget->Start(m_Interface);

	m_BackgroundWidget->SetColor(Color(35, 35, 35, 225), Color(5, 5, 5, 225));

	m_BackgroundWidget->SetPos(10, 35);
	m_BackgroundWidget->SetSize(m_Interface->m_Base->m_Settings->m_width - 20, 350);

	HFont* headerFont = m_Interface->m_Tier2->m_IWidget->CreateFont("Arame-Mono.ttf", 20, IWidget::EFontFlags::FONTFLAGS_OUTLINE);

	m_TitleWidget = new ITextWidget;
	m_TitleWidget->Start(m_Interface);

	m_TitleWidget->SetFont(headerFont);
	m_TitleWidget->SetText("Console");

	m_TitleWidget->SetPos(15, 12.5);

	HFont* consoleFont = m_Interface->m_Tier2->m_IWidget->CreateFont("Arame-Mono.ttf", 16, IWidget::EFontFlags::FONTFLAGS_OUTLINE);

	m_InputWidget = new IEditField;
	m_InputWidget->Start(m_Interface);

	m_InputWidget->SetColor(Color(25, 25, 25, 255));
	m_InputWidget->SetFont(consoleFont);

	m_InputWidget->SetEvent(std::bind(&IConsole::ProcessCommand, this, std::placeholders::_1));

	m_InputWidget->SetPos(20, (m_Interface->m_Base->m_Settings->m_height / 2) - 10.f);
	m_InputWidget->SetSize(m_Interface->m_Base->m_Settings->m_width - 40, 25);

	m_OutputWidget = new ITextWidget;
	m_OutputWidget->Start(m_Interface);

	m_OutputWidget->SetFont(consoleFont);

	m_OutputWidget->SetPos(20, 40);

	m_Active = false;

	m_HeaderWidget->SetHidden(true);
	m_BackgroundWidget->SetHidden(true);

	m_TitleWidget->SetHidden(true);

	m_InputWidget->SetHidden(true);
	m_OutputWidget->SetHidden(true);
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
	if (wiInput::Press(wiInput::BUTTON::KEYBOARD_BUTTON_F1))
	{
		m_Active = !m_Active;
		if (m_Active)
		{
			m_HeaderWidget->SetHidden(false);
			m_BackgroundWidget->SetHidden(false);

			m_TitleWidget->SetHidden(false);

			m_InputWidget->SetHidden(false);
			m_OutputWidget->SetHidden(false);

			m_InputWidget->m_Flags = IWidget::EWidgetFlags::FONTFLAGS_FOCUSED;
		}
		else
		{
			m_HeaderWidget->SetHidden(true);
			m_BackgroundWidget->SetHidden(true);

			m_TitleWidget->SetHidden(true);

			m_InputWidget->SetHidden(true);
			m_OutputWidget->SetHidden(true);
		}
	}

	if (m_Active)
	{
		while (m_Lines >= 19)
		{
			std::string wherestr = m_Output.substr(0, m_Output.find_first_of("\n"));
			Utils::string_remove_line(m_Output, wherestr);
			m_Lines--;
		}
		m_OutputWidget->SetText(m_Output.c_str());
	}
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
// Processing a given command
//-----------------------------------------------------------------------------
void IConsole::ProcessCommand(const char* command)
{
	bool skip = false;

	std::string commandToProcess = command;
	std::string commandNoArgs = commandToProcess.substr(0, commandToProcess.find(" ", 0));
	for (size_t i = 0; i < m_Cvars.capacity(); i++)
	{
		std::string cvar = m_Cvars[i]->m_Cvar.m_Command;
		if (commandNoArgs == cvar)
		{
			std::string commandArgs;
			if (commandToProcess.length() > commandNoArgs.length())
			{
				commandArgs = commandToProcess.substr(commandNoArgs.length() + 1);
			}

			if (Utils::is_string_float(commandArgs) && !Utils::is_string_int(commandArgs))
			{
				ExecuteCommand(cvar.c_str(), std::stof(commandArgs.c_str()));
			}
			else if (Utils::is_string_int(commandArgs))
			{
				ExecuteCommand(cvar.c_str(), std::stoi(commandArgs.c_str()));
			}
			else
			{
				ExecuteCommand(cvar.c_str(), commandArgs.c_str());
			}
		}
		else
		{
			bool found = false;

			if (!skip)
			{
				for (size_t i = 0; i < m_Cvars.capacity(); i++)
				{
					std::string cvarToSearch = m_Cvars[i]->m_Cvar.m_Command;
					if (commandNoArgs == cvarToSearch)
					{
						found = true;
					}
				}

				if (!found)
				{
					std::string error;
					error.append("Unknown command ");
					error.append(commandNoArgs);
					LogCommand(error.c_str());

					skip = true;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Executes a given command
//-----------------------------------------------------------------------------
void IConsole::InternalExecuteCommand(const char* command, const char* args, float fargs, int iargs)
{
	std::string commandStr = command;

	bool found = false;

	if (commandStr == "mat_vsync")
	{
		Callback_mat_vsync(iargs);
		found = true;
	}
	if (commandStr == "mat_mode")
	{
		Callback_mat_mode(iargs);
		found = true;
	}
	if (commandStr == "clear")
	{
		Callback_clear();
		found = true;
	}
	if (commandStr == "quit")
	{
		Callback_quit();
		found = true;
	}

	if (found)
	{
		std::string info;
		info.append("] ");
		info.append(command);
		info.append(" ");
		if (Utils::is_string_float(args) && !Utils::is_string_int(args))
		{
			info.append(std::to_string(fargs));
		}
		else if (Utils::is_string_int(args))
		{
			info.append(std::to_string(iargs));
		}
		else
		{
			info.append(args);
		}

		if (commandStr != "clear")
		{
			LogCommand(info.c_str());
		}
	}
	else
	{
		std::string error;
		error.append("Unknown command ");
		error.append(command);
		LogCommand(error.c_str());
	}
}

//-----------------------------------------------------------------------------
// Logs a text into console window
//-----------------------------------------------------------------------------
void IConsole::LogCommand(const char* text)
{
	m_Output.append(text);
	m_Output.append("\n");
	m_Lines++;
}

//-----------------------------------------------------------------------------
// Callbacks for given commands
//-----------------------------------------------------------------------------
void IConsole::Callback_mat_vsync(int value)
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

void IConsole::Callback_mat_mode(int value)
{
	if (value > 0)
	{
		wiRenderer::SetWireRender(true);
	}
	else
	{
		wiRenderer::SetWireRender(false);
	}
}

void IConsole::Callback_clear()
{
	m_Output.clear();
	m_Lines = 0;
}

void IConsole::Callback_quit()
{
	exit(0);
}
