/*
    File: IHelicopter.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btVector3.h>

class IInterfaces;

class IObject;

class IHelicopter
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IHelicopter initalization process
    void Start(IInterfaces* interfaces);

    // Activates IHelicopter shutdown process
    void Stop();

    // Processing a single frame of IHelicopter
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
};