/*
    File: IGame.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

class IInterfaces;

class IGame
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IDirect2D initialization process
    void Start(IInterfaces* interfaces);

    // Activates IDirect2D shutdown process
    void Stop();

    // Processing a single frame of IDirect2D
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