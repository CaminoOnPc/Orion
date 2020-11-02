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

	wiScene::TransformComponent transform;
	transform.RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z)));
	transform.Translate(XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
	transform.UpdateTransform();
	
	wiScene::LoadModel(m_Data.m_ModelName, transform.GetLocalMatrix());
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