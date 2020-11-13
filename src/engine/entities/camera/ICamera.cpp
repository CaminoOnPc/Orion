/*
	File: ICamera.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "ICamera.h"

//-----------------------------------------------------------------------------
// Activates ICamera initalization process
//-----------------------------------------------------------------------------
void ICamera::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	m_Position = Vector(0, 0, 0);
	m_Rotation = Vector(0, 0, 0);

	m_ViewAspectRatio = m_Interface->m_Base->m_Settings->m_width / m_Interface->m_Base->m_Settings->m_height;
	m_ViewDistance = 10000.0f;
	m_ViewFov = 0.4f * 3.14f;

	m_Near = 1.0f;
	m_Far = 10000.0f;
}

//-----------------------------------------------------------------------------
// Activates ICamera shutdown process
//-----------------------------------------------------------------------------
void ICamera::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of ICamera
//-----------------------------------------------------------------------------
void ICamera::Run(float dt)
{
	if (m_IsActive)
	{
		wiScene::TransformComponent transform;

		transform.RotateRollPitchYaw(XMFLOAT3(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z)));
		transform.Translate(XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
		transform.UpdateTransform();

		wiScene::CameraComponent& camera = wiRenderer::GetCamera();
		camera.TransformCamera(transform);
		camera.UpdateCamera();
	}
}