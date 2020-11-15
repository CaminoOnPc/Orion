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

	m_UI = wiSprite("data/game/materials/textures/ui/ui.png");
	m_UI.params.sampleFlag = SAMPLEMODE_CLAMP;
	m_UI.params.blendFlag = BLENDMODE_ALPHA;
	m_UI.params.quality = QUALITY_LINEAR;
	m_UI.params.pos = XMFLOAT3(0, 0, 0.0f);
	m_UI.params.enableFullScreen();

	RenderPath2D* path = (RenderPath2D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	path->AddSprite(&m_UI);

	//m_Interface->m_Tier2->m_IConsole->Start(m_Interface);

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



	IGradientWidget* gradient = new IGradientWidget;
	gradient->Start(m_Interface);

	gradient->SetColor(Color(255, 255, 0), Color(255, 0, 255));
	gradient->SetPos(0, 100);
	gradient->SetSize(100, 100);

	//gradient->SetHidden(true);
	//gradient->SetHidden(false);

	m_Interface->m_Tier2->m_IConsole->ExecuteCommand("r_vsync", 1);

	m_Interface->m_Tier2->m_IConsole->ExecuteCommand("fff", 1);


	// TODO:

	// https://i.ytimg.com/vi/4xHuXq4VvGE/maxresdefault.jpg
	// https://www.youtube.com/watch?v=uk6-Oq-lr2Y
	// Gradient for console title like that
	// Finish console functionallity

	// Fix/tests shadow and outline for text
	

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
			m_DebugCamera->Run(dt);
		}

		if (m_DebugDisplay)
		{
			m_DebugDisplay->Run(dt);
		}	

		m_Interface->m_Tier2->m_IConsole->Run(dt);
	}
}