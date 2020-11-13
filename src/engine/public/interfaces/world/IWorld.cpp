/*
	File: IWorld.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IWorld.h"

//-----------------------------------------------------------------------------
// Activates IWorld initalization process
//-----------------------------------------------------------------------------
void IWorld::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
}

//-----------------------------------------------------------------------------
// Activates IWorld shutdown process
//-----------------------------------------------------------------------------
void IWorld::Stop()
{
	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of IWorld
//-----------------------------------------------------------------------------
void IWorld::Run(float dt)
{
	for (size_t i = 0; i < m_Objects.capacity(); i++)
	{
		m_Objects[i]->Run(dt);
	}

	for (size_t i = 0; i < m_Sounds.capacity(); i++)
	{
		m_Sounds[i]->Run(dt);
	}
}

//-----------------------------------------------------------------------------
// Creates and loads a world
//-----------------------------------------------------------------------------
void IWorld::CreateWorld(const char* world)
{
	m_World = wiScene::LoadModel(world);

	Color horizon = Color(101, 101, 227);
	Color ambient = Color(33, 47, 127);
	Color zenith = Color(99, 133, 255);

	auto& weather = wiScene::GetScene().weathers.Create(wiECS::CreateEntity());
	weather.cloudiness = 0.0f;
	weather.horizon = XMFLOAT3(horizon.rBase(), horizon.gBase(), horizon.bBase());
	weather.ambient = XMFLOAT3(ambient.rBase(), ambient.gBase(), ambient.bBase());
	weather.zenith = XMFLOAT3(zenith.rBase(), zenith.gBase(), zenith.bBase());
	weather.SetRealisticSky(true);

	RenderPath3D* path = (RenderPath3D*)m_Interface->m_Tier0->m_Rendering->m_RenderPath;
	if (path)
	{
		path->setVolumetricCloudsEnabled(true);

		for (size_t i = 0; i < wiScene::GetScene().lights.GetCount(); i++)
		{
			wiScene::LightComponent* light = wiScene::GetScene().lights.GetComponent(wiScene::GetScene().lights.GetEntity(i));
			if (light->type == wiScene::LightComponent::LightType::DIRECTIONAL)
			{
				wiScene::TransformComponent* transform = wiScene::GetScene().transforms.GetComponent(wiScene::GetScene().Entity_FindByName("sun"));
				if (transform)
				{
					transform->ClearTransform();
					transform->RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(45), XMConvertToRadians(0), XMConvertToRadians(0)));
					transform->Translate(XMFLOAT3(0, 0, 0));
					transform->UpdateTransform();
				}

				for (size_t i = 1; i < 15; i++)
				{
					std::string flare = "data/game/materials/textures/effects/flare_";
					flare.append(std::to_string(i));
					flare.append(".png");

					light->lensFlareRimTextures.push_back(wiResourceManager::Load(flare));
					light->lensFlareNames.push_back(flare);
				}
			}
		}
	}

	m_WorldName = world;
	Utils::string_replace(m_WorldName, ".wiscene", ".ent");
}

//-----------------------------------------------------------------------------
// Creates and loads new object
//-----------------------------------------------------------------------------
IObject* IWorld::CreateObject(const char* model, Vector position, Vector rotation)
{
	IObject* object = new IObject;
	if (!object)
	{
		// TODO@: Add assert message (Warning)
		return nullptr;
	}

	object->m_Position = position;
	object->m_Rotation = rotation;

	for (size_t i = 0; i < m_Interface->m_Tier2->m_IFileSystem->m_Objects.capacity(); i++)
	{
		for (std::vector<HObject*>::reverse_iterator i = m_Interface->m_Tier2->m_IFileSystem->m_Objects.rbegin(); i != m_Interface->m_Tier2->m_IFileSystem->m_Objects.rend(); ++i)
		{
			HObject* objects = *i;
			if (objects->m_ModelName == model)
			{
				object->m_Data.m_ModelName = objects->m_ModelPath.c_str();
			}
		}
	}

	object->Start(m_Interface);

	m_Objects.push_back(object);
	return object;
}

//-----------------------------------------------------------------------------
// Deletes existing object
//-----------------------------------------------------------------------------
void IWorld::ObjectDelete(IObject* object)
{
	for (int i = 0; i < m_Objects.capacity(); i++)
	{
		if (m_Objects[i] == object)
		{
			SafeRelease(&m_Objects.at(i));
		}
	}
}

//-----------------------------------------------------------------------------
// Creates and loads new sound in 3D
//-----------------------------------------------------------------------------
ISound* IWorld::CreateSoundObject(const char* audio, float distance, Vector position)
{
	ISound* sound = new ISound;
	if (!sound)
	{
		// TODO@: Add assert message (Warning)
		return nullptr;
	}

	sound->m_Data.m_SoundName = audio;

	sound->m_Data.m_SoundDistance = distance;
	sound->m_Data.m_SoundType = 0;

	sound->m_Position = position;

	sound->Start(m_Interface);

	m_Sounds.push_back(sound);
	return sound;
}

// ---------------------------------------------------------------------------- -
// Creates and loads new sound in 2D
//-----------------------------------------------------------------------------
ISound * IWorld::CreateSoundObject2D(const char* audio)
{
	ISound* sound = new ISound;
	if (!sound)
	{
		// TODO@: Add assert message (Warning)
		return nullptr;
	}

	sound->m_Data.m_SoundName = audio;
	sound->m_Data.m_SoundType = 1;

	sound->Start(m_Interface);

	m_Sounds.push_back(sound);
	return sound;
}

//-----------------------------------------------------------------------------
// Deletes existing sound
//-----------------------------------------------------------------------------
void IWorld::SoundObjectDelete(ISound* sound)
{
	for (int i = 0; i < m_Sounds.capacity(); i++)
	{
		if (m_Sounds[i] == sound)
		{
			SafeRelease(&m_Sounds.at(i));
		}
	}
}