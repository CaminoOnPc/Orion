/*
	File: ISound.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "ISound.h"

//-----------------------------------------------------------------------------
// Activates ISound initalization process
//-----------------------------------------------------------------------------
void ISound::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;
	
	m_Entity = wiScene::GetScene().Entity_CreateSound("sound", m_Data.m_SoundName, XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
	if (m_Entity)
	{
		m_SoundComponent = wiScene::GetScene().sounds.GetComponent(m_Entity);
		if (m_SoundComponent)
		{
			m_SoundComponent->soundResource = wiResourceManager::Load(m_Data.m_SoundName);
			m_SoundComponent->filename = m_Data.m_SoundName;
			wiAudio::CreateSoundInstance(m_SoundComponent->soundResource->sound, &m_SoundComponent->soundinstance);

			if (m_Data.m_SoundType == 0)
			{
				m_SoundComponent->SetDisable3D(false);
			}
			else if (m_Data.m_SoundType == 1)
			{
				m_SoundComponent->SetDisable3D(true);
			}

			m_SoundComponent->Play();
		}
	}
}

//-----------------------------------------------------------------------------
// Activates ISound shutdown process
//-----------------------------------------------------------------------------
void ISound::Stop()
{
	if (m_SoundComponent)
	{
		m_SoundComponent->Stop();
	}

	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of ISound
//-----------------------------------------------------------------------------
void ISound::Run()
{
	if (m_Data.m_SoundType == 0)
	{
		if (m_SoundComponent)
		{
			wiScene::CameraComponent& camera = wiRenderer::GetCamera();

			float volume = (
				m_Data.m_SoundDistance - m_Position.Distance(
					Vector(camera.Eye.x, camera.Eye.y, camera.Eye.z)
				)) / m_Data.m_SoundDistance;
			if (volume < 0)
			{
				volume = 0;
			}

			m_SoundComponent->volume = volume;
		}
	}
}

//-----------------------------------------------------------------------------
// Sets an audio position
//-----------------------------------------------------------------------------
void ISound::SetPosition(Vector position)
{
	m_Position = position;
}

//-----------------------------------------------------------------------------
// Returns an audio position
//-----------------------------------------------------------------------------
Vector ISound::GetPosition()
{
	return m_Position;
}

//-----------------------------------------------------------------------------
// Stops the audio playback
//-----------------------------------------------------------------------------
void ISound::StopSound()
{
	if (!m_SoundComponent->IsPlaying())
	{
		m_SoundComponent->Stop();
	}
}

//-----------------------------------------------------------------------------
// Starts the audio playback
//-----------------------------------------------------------------------------
void ISound::PlaySound()
{
	if (!m_SoundComponent->IsPlaying())
	{
		m_SoundComponent->Play();
	}
}
