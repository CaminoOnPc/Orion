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
	
	m_SoundComponent = wiScene::GetScene().sounds.Create(wiECS::CreateEntity());
	m_SoundComponent.filename = m_Data.m_SoundName;
	m_SoundComponent.soundResource = wiResourceManager::Load(m_Data.m_SoundName);
	wiAudio::CreateSoundInstance(m_SoundComponent.soundResource->sound, &m_SoundComponent.soundinstance);
}

//-----------------------------------------------------------------------------
// Activates ISound shutdown process
//-----------------------------------------------------------------------------
void ISound::Stop()
{
	wiAudio::Stop(&m_SoundInstance);

	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of ISound
//-----------------------------------------------------------------------------
void ISound::Run()
{
	if (m_Data.m_SoundType == 0)
	{
		const wiScene::CameraComponent& camera = wiRenderer::GetCamera();
		wiAudio::SoundInstance3D instance3D;
		instance3D.listenerPos = camera.Eye;
		instance3D.listenerUp = camera.Up;
		instance3D.listenerFront = camera.At;

		instance3D.emitterPos = XMFLOAT3(m_Position.x, m_Position.y, m_Position.z);
		wiAudio::Update3D(&m_SoundInstance, instance3D);

		if (m_SoundComponent.IsPlaying())
		{
			wiAudio::Play(&m_SoundComponent.soundinstance);
		}
		else
		{
			wiAudio::Stop(&m_SoundComponent.soundinstance);
		}

		if (!m_SoundComponent.IsLooped())
		{
			wiAudio::ExitLoop(&m_SoundComponent.soundinstance);
		}

		wiAudio::SetVolume(m_SoundComponent.volume, &m_SoundComponent.soundinstance);
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
// Pauses the audio playback
//-----------------------------------------------------------------------------
void ISound::Pause()
{
	if (m_SoundComponent.IsPlaying())
	{
		wiAudio::Pause(&m_SoundComponent.soundinstance);
	}
}

//-----------------------------------------------------------------------------
// Stops the audio playback
//-----------------------------------------------------------------------------
void ISound::Stop()
{
	if (!m_SoundComponent.IsPlaying())
	{
		wiAudio::Stop(&m_SoundComponent.soundinstance);
	}
}

//-----------------------------------------------------------------------------
// Starts the audio playback
//-----------------------------------------------------------------------------
void ISound::Play()
{
	if (!m_SoundComponent.IsPlaying())
	{
		wiAudio::Play(&m_SoundComponent.soundinstance);
	}
}
