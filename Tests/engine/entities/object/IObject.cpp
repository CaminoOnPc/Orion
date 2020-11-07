/*
	File: IObject.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IObject.h"

//-----------------------------------------------------------------------------
// Activates IObject initalization process
//-----------------------------------------------------------------------------
void IObject::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	ICache* cached = nullptr;
	bool skip = false;
	for (size_t i = 0; i < m_Interface->m_Tier2->m_IWorld->m_Cache.size(); i++)
	{
		ICache* cache = m_Interface->m_Tier2->m_IWorld->m_Cache.at(i);
		if (cache->m_ModelName == m_Data.m_ModelName)
		{
			cached = cache;
			skip = true;
		}
	}

	if (skip)
	{
		wiECS::Entity duplicate = wiScene::GetScene().Entity_Duplicate(cached->m_Entity);
		if (duplicate)
		{
			std::cout << "Duplicate: " << (void*)duplicate << std::endl;

			wiScene::GetScene().transforms.Create(duplicate);
			wiScene::TransformComponent* transform = wiScene::GetScene().transforms.GetComponent(duplicate);
			if (transform)
			{
				std::cout << "Transform: " << (void*)transform << std::endl;

				transform->RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z)));
				transform->Translate(XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
				transform->UpdateTransform();

				std::cout << "Position: " << m_Position.x << " " << m_Position.y << " " << m_Position.z << " " << std::endl;
			}
		}
		return;
	}

	wiScene::TransformComponent transform;
	transform.RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z)));
	transform.Translate(XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
	transform.UpdateTransform();

	wiECS::Entity entity = wiScene::LoadModel(m_Data.m_ModelName, transform.GetLocalMatrix());

	cached = new ICache;
	cached->m_ModelName = m_Data.m_ModelName;
	cached->m_Entity = entity;

	m_Interface->m_Tier2->m_IWorld->m_Cache.push_back(cached);
}

//-----------------------------------------------------------------------------
// Loads a model and moves it onto specified coordinates
//-----------------------------------------------------------------------------
void IObject::LoadModel()
{
	
}

//-----------------------------------------------------------------------------
// Activates IObject shutdown process
//-----------------------------------------------------------------------------
void IObject::Stop()
{
	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of IObject
//-----------------------------------------------------------------------------
void IObject::Run()
{
}

//-----------------------------------------------------------------------------
// Sets an object scale
//-----------------------------------------------------------------------------
void IObject::SetScale(Vector scale)
{
	m_Scale = scale;
}

//-----------------------------------------------------------------------------
// Returns an object scale
//-----------------------------------------------------------------------------
Vector IObject::GetScale()
{
	return m_Scale;
}

//-----------------------------------------------------------------------------
// Sets an object rotation
//-----------------------------------------------------------------------------
void IObject::SetRotation(Vector rotation)
{
	m_Rotation = rotation;
}

//-----------------------------------------------------------------------------
// Returns an object rotation
//-----------------------------------------------------------------------------
Vector IObject::GetRotation()
{
	return m_Rotation;
}

//-----------------------------------------------------------------------------
// Sets an object position
//-----------------------------------------------------------------------------
void IObject::SetPosition(Vector position)
{
	m_Position = position;
}

//-----------------------------------------------------------------------------
// Returns an object position
//-----------------------------------------------------------------------------
Vector IObject::GetPosition()
{
	return m_Position;
}