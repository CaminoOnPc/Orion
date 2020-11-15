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
	

	m_Background = new IImageWidget;
	m_Background->Start(m_Interface);

	m_Background->SetColor(Color(75, 75, 75, 255));
	m_Background->SetPos(10, 10);
	m_Background->SetSize(m_Interface->m_Base->m_Settings->m_width - 20, (m_Interface->m_Base->m_Settings->m_height / 2) - 10);

	m_Input = new IImageWidget;
	m_Input->Start(m_Interface);
	
	m_Input->SetColor(Color(50, 50, 50, 255));
	m_Input->SetPos(10, (m_Interface->m_Base->m_Settings->m_height / 2) + 10.f);
	m_Input->SetSize(m_Interface->m_Base->m_Settings->m_width - 20, 25);

	HFont* font = m_Interface->m_Tier2->m_IWidget->CreateFont("ApexMk2-Regular.otf", 16, IWidget::EFontFlags::FONTFLAGS_OUTLINE);

	std::string outputText;
	outputText.append(m_Output);

	m_OutputText = new ITextWidget;
	m_OutputText->Start(m_Interface);

	m_OutputText->SetFont(font);
	m_OutputText->SetPos(20, 20);

	m_Active = true;
}

//-----------------------------------------------------------------------------
// Activates IConsole shutdown process
//-----------------------------------------------------------------------------
void IConsole::Stop()
{
	m_Interface = nullptr;
}

void RemoveLine(std::string& source, const std::string& to_remove)
{
	size_t m = source.find(to_remove);
	size_t n = source.find_first_of("\n", m + to_remove.length());
	source.erase(m, n - m + 1);
}

//-----------------------------------------------------------------------------
// Processing a single frame of IConsole
//-----------------------------------------------------------------------------
void IConsole::Run(float dt)
{
	if (wiInput::Down((wiInput::BUTTON)'S'))
	{
		ExecuteCommand("vvv", 1);
	}

	if (wiInput::Press(wiInput::BUTTON::KEYBOARD_BUTTON_F1))
	{
		RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;

		m_Active = !m_Active;
		if (m_Active)
		{
			//path->AddFont(&m_OutputText);
			//path->AddFont(&m_InputText);
			//path->AddSprite(&m_Background);
			//path->AddSprite(&m_Input);
		}
		else
		{
			//path->RemoveFont(&m_OutputText);
			//path->RemoveFont(&m_InputText);
			//path->RemoveSprite(&m_Background);
			//path->RemoveSprite(&m_Input);
		}
		// 19 lines should be the limit


		//m_Output.erase('\n');
	}

	// Bugs:
	// F1 causes everything to break
	// Last line is cleaned when it shouldnt

	if (m_Active)
	{
		m_OutputText->SetText(m_Output.c_str());
		if (m_Lines >= 19)
		{

			std::string wherestr = m_Output.substr(0, m_Output.find_first_of("\n"));
			RemoveLine(m_Output, wherestr);

			std::cout << wherestr << std::endl;
			//m_Output.erase(0, m_Output.find_first_of("\n"));
			//m_Output.erase(1, m_Output.find_first_of("\n"));
			m_Lines--;
		}
	}

	//std::cout << m_Lines << std::endl;
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
	bool found = false;

	if (command == "r_vsync")
	{
		Callback_r_vsync(iargs);
		found = true;
	}

	if (found)
	{
		std::string info;
		info.append("] ");
		info.append(command);
		LogCommand(info.c_str());
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
