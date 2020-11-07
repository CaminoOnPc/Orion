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
	wiFont::SetFontPath(Utils::get_font_directory());
	wiRenderer::SetShaderPath("data/engine/shadercache/");

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
		ActivatePath(&*m_Renderer);
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
	// Demonstrates that loading screen is working
	Sleep(1000);

	m_Interface->m_Tier0->m_Rendering->m_RenderPath = this;

	
	
	/*
	wiScene::TransformComponent transform;
	transform.Translate(XMFLOAT3(0, 2.f, -4.5f));
	transform.UpdateTransform();
	wiRenderer::GetCamera().TransformCamera(transform);

	int counter = 0;
	wiScene::LoadModel("data/game/objects/models/marvin/marvin.wiscene");
	wiProfiler::SetEnabled(true);
	wiScene::Scene& scene = wiScene::GetScene();
	scene.Entity_CreateLight("testlight", XMFLOAT3(0, 2, -4), XMFLOAT3(1, 1, 1), 4, 10);
	//wiECS::Entity suzanne = scene.Entity_FindByName("Suzanne");
	const float scale = 0.05f;
	int count = 8;
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			counter++;
			wiECS::Entity entity = wiScene::LoadModel(scene, "data/game/objects/models/marvin/marvin.wiscene");
		}
	}
	std::cout << counter << std::endl;
	//scene.Entity_Remove(suzanne);


		//wiScene::LoadModel("data/game/worlds/sponza.wiscene");
	//wiScene::GetScene();
	//wiRenderer::ClearWorld();

	//wiScene::LoadModel("data/game/objects/models/marvin/marvin.wiscene");
	///wiProfiler::SetEnabled(true);
	//wiScene::Scene& scene = wiScene::GetScene();
	//scene.Entity_CreateLight("testlight", XMFLOAT3(0, 2, -4), XMFLOAT3(1, 1, 1), 4, 10);

	//int count = 8;
	//for (int i = 0; i < count; ++i)
	//{
	//	for (int j = 0; j < count; ++j)
	//	{
	//		wiECS::Entity entity = wiScene::LoadModel(scene, "data/game/objects/models/marvin/marvin.wiscene");
	//	}
	//}

	//scene.Entity_Remove(suzanne);

	/*
	int count = 0;

	for (size_t i = 0; i < 25; i++)
	{
		float x = i * 6;
		if (x < 4500)
		{
			for (size_t j = 0; j < 25; j++)
			{
				float z = j * 6;
				if (z < 3500)
				{
					count++;
					std::cout << count << std::endl;

					wiScene::TransformComponent transform;
					transform.RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(0), XMConvertToRadians(0), XMConvertToRadians(0)));
					transform.Translate(XMFLOAT3(x, 0, z));
					transform.UpdateTransform();

					wiScene::Scene modelscene;
					wiScene::LoadModel(modelscene, "data/game/objects/models/marvin/marvin.wiscene", transform.GetLocalMatrix());

					wiScene::GetScene().Merge(modelscene);
				}
			}
		}
	}
	*/

	//static HFont* font = m_Interface->m_Tier2->m_ISurface->CreateFont("Arial", 16, ISurface::EFontFlags::FONTFLAGS_NONE);
	//m_Interface->m_Tier2->m_ISurface->DrawText(font, "Test", 10, 10, Color(255, 255, 255));
	
	RenderPath3D::Load();

	m_Interface->m_Tier3->m_IGame->Start(m_Interface);

}

//-----------------------------------------------------------------------------
// Processing a single frame of IWickedRenderer
//-----------------------------------------------------------------------------
void IWickedRenderer::Update(float dt)
{
	if (m_Interface->m_Tier3->m_IGame)
	{
		m_Interface->m_Tier3->m_IGame->Run(dt);
	}

	RenderPath3D::Update(dt);
}
