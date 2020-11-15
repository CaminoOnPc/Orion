/*
    File: IDebugCamera.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../../../../entities/camera/ICamera.h"

class ICamera;

class IInterfaces;

class IDebugCamera
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IWorld initalization process
    void Start(IInterfaces* interfaces);

    // Activates IWorld shutdown process
    void Stop();

    // Processing a single frame of IWorld
    void Run(float dt);

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
    ICamera* m_Camera;
};