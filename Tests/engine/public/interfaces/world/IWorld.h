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
class ICache;

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
        
    void CreateWorld(const char* world);

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
    wiECS::Entity m_World;
public:
    std::vector< IObject* > m_Objects;
    std::vector< ISound* > m_Sounds;
    std::vector< ICache* > m_Cache;
};

class ICache
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
    const char* m_ModelName;
public:
    wiECS::Entity m_Entity;
};