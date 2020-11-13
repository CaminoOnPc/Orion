/*
    File: ILoading.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class ILoading : public LoadingScreen
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates ILoading initalization process
    void Start(IInterfaces* interfaces);

    // Activates ILoading loading process
    void Load() override;

    // Processing a single frame of ILoading
    void Update(float dt) override;

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
    wiSpriteFont m_Font;
    wiSprite m_Image;
};