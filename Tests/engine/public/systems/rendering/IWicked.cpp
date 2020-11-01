/*
	File: IWicked.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IWicked.h"

//-----------------------------------------------------------------------------
// Activates IRendering initalization process
//-----------------------------------------------------------------------------
void IWicked::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IWicked initalization process
//-----------------------------------------------------------------------------
void IWicked::Initialize()
{
	MainComponent::Initialize();

	m_Loading = new ILoading;
	if (!m_Loading)
	{
		return;
	}

	m_Loading->Start(m_Interface);

	m_Renderer = new IWickedRenderer;
	if (!m_Renderer)
	{
		return;
	}

	m_Renderer->Start(m_Interface);

	m_Loading->addLoadingComponent(&*m_Renderer, this, 0.2f);
	ActivatePath(&*m_Loading, 0.2f);
	m_Loading->onFinished([&] 
	{
		m_Renderer->Load();
		ActivatePath(&*m_Renderer);

		m_Interface->m_Tier3->m_IGame->Start(m_Interface);
	});
}

//-----------------------------------------------------------------------------
// Activates IRendering initalization process
//-----------------------------------------------------------------------------
void IWickedRenderer::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IWickedRenderer initalization process
//-----------------------------------------------------------------------------
void IWickedRenderer::Load()
{
	m_Interface->m_Tier0->m_Rendering->m_RenderPath = this;

	setSSREnabled(false);
	setReflectionsEnabled(true);
	setFXAAEnabled(false);

	/*
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

	static wiComboBox testSelector;
	testSelector.Create("TestSelector");
	testSelector.SetText("Demo: ");
	testSelector.SetSize(XMFLOAT2(140, 20));
	testSelector.SetPos(XMFLOAT2(50, 200));
	testSelector.SetColor(wiColor(255, 205, 43, 200), wiWidget::WIDGETSTATE::IDLE);
	testSelector.SetColor(wiColor(255, 235, 173, 255), wiWidget::WIDGETSTATE::FOCUS);
	testSelector.AddItem("HelloWorld");
	testSelector.AddItem("Model");
	testSelector.AddItem("EmittedParticle 1");
	testSelector.AddItem("EmittedParticle 2");
	testSelector.AddItem("HairParticle");
	testSelector.AddItem("Lua Script");
	testSelector.AddItem("Water Test");
	testSelector.AddItem("Shadows Test");
	testSelector.AddItem("Physics Test");
	testSelector.AddItem("Cloth Physics Test");
	testSelector.AddItem("Job System Test");
	testSelector.AddItem("Font Test");
	testSelector.AddItem("Volumetric Test");
	testSelector.AddItem("Sprite Test");
	testSelector.AddItem("Lightmap Bake Test");
	testSelector.AddItem("Network Test");
	testSelector.AddItem("Controller Test");
	testSelector.AddItem("Inverse Kinematics");
	testSelector.AddItem("65k Instances");
	testSelector.SetMaxVisibleItemCount(10);

	testSelector.OnSelect([=](wiEventArgs args) {

		// Reset all state that tests might have modified:
		wiRenderer::GetDevice()->SetVSyncEnabled(true);
		wiRenderer::SetToDrawGridHelper(false);
		wiRenderer::SetTemporalAAEnabled(false);
		wiRenderer::ClearWorld();
		wiScene::GetScene().weather = wiScene::WeatherComponent();
		this->ClearSprites();
		this->ClearFonts();
		if (wiLua::GetLuaState() != nullptr) {
			wiLua::KillProcesses();
		}

		// Reset camera position:
		wiScene::TransformComponent transform;
		transform.Translate(XMFLOAT3(0, 2.f, -4.5f));
		transform.UpdateTransform();
		wiRenderer::GetCamera().TransformCamera(transform);

		float screenW = wiRenderer::GetDevice()->GetScreenWidth();
		float screenH = wiRenderer::GetDevice()->GetScreenHeight();

		// Based on combobox selection, start the appropriate test:
		switch (args.iValue)
		{
		case 0:
		{
			break;
		}
		case 1:
			wiRenderer::SetTemporalAAEnabled(true);
			wiScene::LoadModel("data/game/worlds/sponza.wiscene");
			break;

		default:
			assert(0);
			break;
		}
	});

	testSelector.SetSelected(0);
	GetGUI().AddWidget(&testSelector);
	*/

	RenderPath3D::Load();
}

//-----------------------------------------------------------------------------
// Processing a single frame of IWickedRenderer
//-----------------------------------------------------------------------------
void IWickedRenderer::Update(float dt)
{
	RenderPath3D::Update(dt);
}
