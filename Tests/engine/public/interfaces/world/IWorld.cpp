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
void IWorld::Run()
{
	for (size_t i = 0; i < m_Objects.capacity(); i++)
	{
		m_Objects[i]->Run();
	}

	for (size_t i = 0; i < m_Sounds.capacity(); i++)
	{
		m_Sounds[i]->Run();
	}
}

//-----------------------------------------------------------------------------
// Creates and loads new object
//-----------------------------------------------------------------------------
IObject* IWorld::CreateObject(const char* model, const char* material, Vector position, Vector rotation)
{
	IObject* object = new IObject;
	if (!object)
	{
		// TODO@: Add assert message (Warning)
		return nullptr;
	}

	object->m_Position = position;
	object->m_Rotation = rotation;

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
ISound* IWorld::CreateSoundObject(const char* audio, float distance, Vector position, Vector rotation)
{
	ISound* sound = new ISound;
	if (!sound)
	{
		// TODO@: Add assert message (Warning)
		return nullptr;
	}

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