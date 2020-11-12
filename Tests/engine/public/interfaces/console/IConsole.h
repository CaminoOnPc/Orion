/*
    File: IConsole.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class IConsole
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IConsole initalization process
    void Start(IInterfaces* interfaces);

    // Activates IConsole shutdown process
    void Stop();

    // Processing a single frame of IConsole
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
};