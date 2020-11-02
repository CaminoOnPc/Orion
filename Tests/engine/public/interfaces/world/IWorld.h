/*
    File: IWorld.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../../../entities/object/IObject.h"
#include "../../../entities/sound/ISound.h"

class IObject;
class ISound;

class IInterfaces;

class IWorld
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IWorld initalization process
    void Start(IInterfaces* interfaces);

    // Activates IWorld shutdown process
    void Stop();

    // Processing a single frame of IWorld
    void Run();

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    IObject* CreateObject(const char* model, const char* material, Vector position, Vector rotation);
    void ObjectDelete(IObject* object);

    ISound* CreateSoundObject(const char* audio, float distance, Vector position, Vector rotation);
    ISound* CreateSoundObject2D(const char* audio);
    void SoundObjectDelete(ISound* object);
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
    std::vector< IObject* > m_Objects;
    std::vector< ISound* > m_Sounds;
};