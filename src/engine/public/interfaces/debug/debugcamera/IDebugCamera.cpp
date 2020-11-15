/*
	File: IDebugCamera.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IDebugCamera.h"

//-----------------------------------------------------------------------------
// Activates IDebugCamera initalization process
//-----------------------------------------------------------------------------
void IDebugCamera::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_Camera = new ICamera;
	if (!m_Camera)
	{
		return;
	}

	m_Camera->Start(m_Interface);

	m_Camera->m_IsActive = true;
	m_Camera->m_Position = Vector(0, 0, 0);
	m_Camera->m_Rotation = Vector(0, 0, 0);

	m_Camera->m_Far = 1000000.f;
}

//-----------------------------------------------------------------------------
// Activates IWorld shutdown process
//-----------------------------------------------------------------------------
void IDebugCamera::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IDebugCamera
//-----------------------------------------------------------------------------
void IDebugCamera::Run(float dt)
{
	wiScene::CameraComponent& camera = wiRenderer::GetCamera();

	float sensitivity = 0.1f;
	float speed = 6.0f * dt;

	if (wiInput::Down((wiInput::BUTTON)'W'))
	{
		m_Camera->m_Position.x += speed * camera.At.x;
		m_Camera->m_Position.y += speed * camera.At.y;
		m_Camera->m_Position.z += speed * camera.At.z;
	}

	if (wiInput::Down((wiInput::BUTTON)'S'))
	{
		m_Camera->m_Position.x -= speed * camera.At.x;
		m_Camera->m_Position.y -= speed * camera.At.y;
		m_Camera->m_Position.z -= speed * camera.At.z;
	}

	if (wiInput::Down((wiInput::BUTTON)'A'))
	{
		XMFLOAT3 normalized;
		XMStoreFloat3(&normalized, XMVector3Normalize(XMVector3Cross(camera.GetAt(), camera.GetUp())));
		m_Camera->m_Position.x += speed * normalized.x;
		m_Camera->m_Position.y += speed * normalized.y;
		m_Camera->m_Position.z += speed * normalized.z;
	}

	if (wiInput::Down((wiInput::BUTTON)'D'))
	{
		XMFLOAT3 normalized;
		XMStoreFloat3(&normalized, XMVector3Normalize(XMVector3Cross(camera.GetAt(), camera.GetUp())));
		m_Camera->m_Position.x -= speed * normalized.x;
		m_Camera->m_Position.y -= speed * normalized.y;
		m_Camera->m_Position.z -= speed * normalized.z;
	}
	
	if (wiInput::Down((wiInput::BUTTON)'Q'))
	{
		m_Camera->m_Position += Vector(0, -1, 0) * speed;
	}

	if (wiInput::Down((wiInput::BUTTON)'E'))
	{
		m_Camera->m_Position += Vector(0, 1, 0) * speed;
	}

	m_Camera->m_Rotation.y += wiInput::GetMouseState().delta_position.x * sensitivity;
	m_Camera->m_Rotation.x += wiInput::GetMouseState().delta_position.y * sensitivity;

	m_Camera->m_Rotation = Math::Clamp(m_Camera->m_Rotation);

	m_Camera->Run(dt);
}