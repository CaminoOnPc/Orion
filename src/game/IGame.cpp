/*
	File: IGame.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IGame.h"

//-----------------------------------------------------------------------------
// Activates IGame initalization process
//-----------------------------------------------------------------------------
void IGame::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_DebugCamera = new IDebugCamera;
	if (!m_DebugCamera)
	{
		return;
	}

	m_DebugCamera->Start(m_Interface);

	m_DebugDisplay = new IDebugDisplay;
	if (!m_DebugDisplay)
	{
		return;
	}

	m_DebugDisplay->Start(m_Interface);

	m_Interface->m_Tier2->m_IWorld->CreateWorld("data/game/worlds/world_empty.wiscene");

	int count = 16;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			IObject* object = m_Interface->m_Tier2->m_IWorld->CreateObject("character_marvin_noai", Vector(float(i) * 4, 0, float(j) * 4), Vector(-90, 0, 0));
			object->SetScale(Vector(1, 1, 1));
		}
	}

	

	//IObject* object = m_Interface->m_Tier2->m_IWorld->CreateObject("zuccini", Vector(float(0) * 4, 0, float(0) * 4), Vector(0, 0, 0));
	//object->SetScale(Vector(100, 100, 100));

	m_UI = new IImageWidget;
	m_UI->Start(m_Interface);

	m_UI->SetImage("data/game/materials/textures/ui/ui.png");

	m_UI->SetPos(0, 0);
	m_UI->SetSize(m_Interface->m_Base->m_Settings->m_width, m_Interface->m_Base->m_Settings->m_height);

	//ui->SetColor(Color(255, 255, 0));
	//ui->SetImage("data/game/materials/textures/effects/flare_9.png");
	//ui->SetPos(0, 0);
	//ui->SetSize(100, 100);

#if DEVELOPER
	m_Interface->m_Tier2->m_IConsole->Start(m_Interface);
#endif

	HFont* consoleFont = m_Interface->m_Tier2->m_IWidget->CreateFont("Arame-Mono.ttf", 16, IWidget::EFontFlags::FONTFLAGS_OUTLINE);


	//IEditField* m_InputTest = new IEditField;
	//m_InputTest->Start(m_Interface);

	//m_InputTest->SetColor(Color(255, 255, 255, 255));

	//m_InputTest->SetFont(consoleFont);
	//m_InputTest->SetText("test");

	//m_InputTest->SetPos(20, 550);
	//m_InputTest->SetSize(m_Interface->m_Base->m_Settings->m_width - 40, 25);

	//ISound* music = m_Interface->m_Tier2->m_IWorld->CreateSoundObject2D("data/game/sounds/sound_music_ambient_1.ogg");
	//music->SetVolume(0.1f);

	//IImageWidget* ui = new IImageWidget;
	//ui->Start(m_Interface);
	//ui->SetColor(Color(255, 255, 0));
	//ui->SetImage("data/game/materials/textures/effects/flare_9.png");
	//ui->SetPos(0, 0);
	//ui->SetSize(100, 100);

	//ui->SetHidden(true);

	//ITextWidget* text = new ITextWidget;
	//text->Start(m_Interface);

	//HFont* font = m_Interface->m_Tier2->m_ISurface->CreateFont("ApexMk2-Regular.otf", 72, IWidget::EFontFlags::FONTFLAGS_OUTLINE);
	//text->SetFont(font);

	//text->SetText("test");

	//text->SetPos(100, 100);



	//IGradientWidget* gradient = new IGradientWidget;
	//gradient->Start(m_Interface);

	//gradient->SetColor(Color(255, 255, 0), Color(255, 0, 255));
	//gradient->SetPos(0, 100);
	//gradient->SetSize(100, 100);

	//gradient->SetHidden(true);
	//gradient->SetHidden(false);

	//m_Interface->m_Tier2->m_IConsole->ExecuteCommand("r_vsync", 1);

	//m_Interface->m_Tier2->m_IConsole->ExecuteCommand("fff", 1);


	// TODO:

	// https://i.ytimg.com/vi/4xHuXq4VvGE/maxresdefault.jpg
	// https://www.youtube.com/watch?v=uk6-Oq-lr2Y
	// Gradient for console title like that
	// Finish console functionallity

	// Fix/tests shadow and outline for text
	// Add *bool update* flag for each operation such as SetText, SetColor etc for widget so that if SetText is used in a 
	// loop it wont hurt performance
	/*
	* if (!update)
	* {
	*	widget->SetText(...)
	* }
	* else
	* {
	*	update();
	* }
	*/
	

	/*
	* TODO@: 
	* Lod support
	* Support for relative paths that go backwards in editor 
	* 
	* Console [Execution done] TODO: GUI console
	* Rework surface interface to behave more like a widget
	* Pottentially add Direct2D back and use it as a widget instead of dynamic panel to save fps (TODO@: Test in Orion V1.0 if that will actually help with fps)
	* 
	* Add scripting language support - squirrel
	* Add archieve system to store assets in them rather than trying to access files dirrectly
	* 
	* Terrain with full support of features that DayZ/Arma supports
	* Tool that converts all DayZ models to usable format
	*/
}

//-----------------------------------------------------------------------------
// Activates IGame shutdown process
//-----------------------------------------------------------------------------
void IGame::Stop()
{
}

//-----------------------------------------------------------------------------
// Processing a single frame of IGame
//-----------------------------------------------------------------------------
void IGame::Run(float dt)
{
	if (m_Interface)
	{
		if (m_DebugCamera)
		{
			if (!m_Interface->m_Tier2->m_IConsole->m_Active)
			{
				m_DebugCamera->Run(dt);
			}
		}

		if (m_DebugDisplay)
		{
			m_DebugDisplay->Run(dt);
		}	

		m_Interface->m_Tier2->m_IConsole->Run(dt);
	}
}