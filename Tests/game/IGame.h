/*
    File: IGame.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class IGame
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IGame initialization process
    void Start(IInterfaces* interfaces);

    // Activates IGame shutdown process
    void Stop();

    // Processing a single frame of IGame
    void Run();

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