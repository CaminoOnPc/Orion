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
		m_Entity = wiScene::GetScene().Entity_Duplicate(cached->m_Entity);
		if (m_Entity)
		{
			wiScene::TransformComponent* transform = wiScene::GetScene().transforms.GetComponent(m_Entity);
			if (transform)
			{	
				transform->ClearTransform();
				transform->RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z)));
				transform->Translate(XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
				transform->UpdateTransform();
			}
		}
		return;
	}

	wiScene::TransformComponent transform;
	transform.RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z)));
	transform.Translate(XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
	transform.UpdateTransform();

	m_Entity = wiScene::LoadModel(m_Data.m_ModelName, transform.GetLocalMatrix(), true);

	cached = new ICache;
	cached->m_ModelName = m_Data.m_ModelName;
	cached->m_Entity = m_Entity;

	m_Interface->m_Tier2->m_IWorld->m_Cache.push_back(cached);
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

	wiScene::TransformComponent* transform = wiScene::GetScene().transforms.GetComponent(m_Entity);
	if (transform)
	{
		transform->RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(rotation.x), XMConvertToRadians(rotation.y), XMConvertToRadians(rotation.z)));
	}
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

	wiScene::TransformComponent* transform = wiScene::GetScene().transforms.GetComponent(m_Entity);
	if (transform)
	{
		transform->Translate(XMFLOAT3(position.x, position.y, position.z));
	}
}

//-----------------------------------------------------------------------------
// Returns an object position
//-----------------------------------------------------------------------------
Vector IObject::GetPosition()
{
	return m_Position;
}