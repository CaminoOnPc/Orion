/*
    File: ISound.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class ISound
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates ISound initialization process
    void Start(IInterfaces* interfaces);

    // Activates ISound shutdown process
    void Stop();

    // Processing a single frame of ISound
    void Run();

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void SetPosition(Vector position);
    Vector GetPosition();

    void StopSound();
    void PlaySound();

    struct EData
    {
        const char* m_SoundName;
        float m_SoundDistance;
        int m_SoundType;
    };

    EData m_Data;

protected:
    IInterfaces* m_Interface;
protected:
    template <class T> void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            *ppT = nullptr;
        }
    }
public:
    wiScene::SoundComponent* m_SoundComponent;
    wiAudio::SoundInstance m_SoundInstance;
    wiAudio::Sound m_Sound;
public:
    wiECS::Entity m_Entity;
public:
    Vector m_Position;
};