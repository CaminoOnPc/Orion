/*
    File: IObject.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class IObject
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IObject initalization process
    void Start(IInterfaces* interfaces);

    // Activates IObject shutdown process
    void Stop();

    // Processing a single frame of IObject
    void Run();

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void SetScale(Vector scale);
    Vector GetScale();

    void SetRotation(Vector rotation);
    Vector GetRotation();

    void SetPosition(Vector position);
    Vector GetPosition();

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
    Vector m_Position;
    Vector m_Rotation;
    Vector m_Scale;
};