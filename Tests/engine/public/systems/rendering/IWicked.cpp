/*
	File: IWicked.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IWicked.h"

//-----------------------------------------------------------------------------
// Activates IWicked initalization process
//-----------------------------------------------------------------------------
void IWicked::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	MainComponent::Initialize();

	infoDisplay.active = true;
	infoDisplay.watermark = false;
	infoDisplay.fpsinfo = true;
	infoDisplay.resolution = true;
	infoDisplay.heap_allocation_counter = true;

	m_Renderer = new IWickedRenderer;
	if (!m_Renderer)
	{
		return;
	}

	m_Renderer->Start(m_Interface);

	m_Renderer->Load();
	ActivatePath(&*m_Renderer);
}

//-----------------------------------------------------------------------------
// Activates IWicked shutdown process
//-----------------------------------------------------------------------------
void IWicked::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IWicked
//-----------------------------------------------------------------------------
void IWicked::Run()
{
	m_Renderer->Run();
}

//-----------------------------------------------------------------------------
// Activates IWickedRenderer initalization process
//-----------------------------------------------------------------------------
void IWickedRenderer::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	setSSREnabled(false);
	setReflectionsEnabled(true);
	setFXAAEnabled(false);

	static wiAudio::Sound sound;
	static wiAudio::SoundInstance soundinstance;

	static wiButton audioTest;
	audioTest.Create("AudioTest");
	audioTest.SetText("Play Test Audio");
	audioTest.SetSize(XMFLOAT2(200, 20));
	audioTest.SetPos(XMFLOAT2(10, 140));
	audioTest.SetColor(wiColor(255, 205, 43, 200), wiWidget::WIDGETSTATE::IDLE);
	audioTest.SetColor(wiColor(255, 235, 173, 255), wiWidget::WIDGETSTATE::FOCUS);
	audioTest.OnClick([&](wiEventArgs args) {
		static bool playing = false;

		if (!sound.IsValid())
		{
			wiAudio::CreateSound("sound/music.wav", &sound);
			wiAudio::CreateSoundInstance(&sound, &soundinstance);
		}

		if (playing)
		{
			wiAudio::Stop(&soundinstance);
			audioTest.SetText("Play Test Audio");
		}
		else
		{
			wiAudio::Play(&soundinstance);
			audioTest.SetText("Stop Test Audio");
		}

		playing = !playing;
		});
	GetGUI().AddWidget(&audioTest);


	static wiSlider volume;
	volume.Create(0, 100, 50, 100, "Volume");
	volume.SetText("Volume: ");
	volume.SetSize(XMFLOAT2(100, 20));
	volume.SetPos(XMFLOAT2(65, 170));
	volume.sprites_knob[wiWidget::WIDGETSTATE::IDLE].params.color = wiColor(255, 205, 43, 200);
	volume.sprites_knob[wiWidget::WIDGETSTATE::FOCUS].params.color = wiColor(255, 235, 173, 255);
	volume.sprites[wiWidget::WIDGETSTATE::IDLE].params.color = wiMath::Lerp(wiColor::Transparent(), volume.sprites_knob[wiWidget::WIDGETSTATE::IDLE].params.color, 0.5f);
	volume.sprites[wiWidget::WIDGETSTATE::FOCUS].params.color = wiMath::Lerp(wiColor::Transparent(), volume.sprites_knob[wiWidget::WIDGETSTATE::FOCUS].params.color, 0.5f);
	volume.OnSlide([](wiEventArgs args) {
		wiAudio::SetVolume(args.fValue / 100.0f, &soundinstance);
		});
	GetGUI().AddWidget(&volume);

	RenderPath3D::Load();
}

//-----------------------------------------------------------------------------
// Activates IWickedRenderer shutdown process
//-----------------------------------------------------------------------------
void IWickedRenderer::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IWickedRenderer
//-----------------------------------------------------------------------------
void IWickedRenderer::Run()
{
	RenderPath3D::Update(0.01);
}