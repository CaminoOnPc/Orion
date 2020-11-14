/*
    File: IWidget.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../HFont.h"
    
class IInterfaces;

class IWidget
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IWidget initalization process
    void Start(IInterfaces* interfaces);

    // Activates IWidget shutdown process
    void Stop();

    // Processing a single frame of IWidget
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    enum EFontFlags
    {
        FONTFLAGS_NONE,
        FONTFLAGS_SHADOW = 0x001,
        FONTFLAGS_OUTLINE = 0x002,
    };

    virtual void SetPos(float x, float y);
    virtual void GetPos(float& x, float& y);

    virtual void SetSize(float x, float y);
    virtual void GetSize(float& height, float& width);

    virtual void SetRotation(float roll);
    virtual void GetRotation(float &roll);

    virtual void SetScale(float height, float width);
    virtual void GetScale(float& height, float& width);

    void GetScreenPos(float &x, float &y);
    void GetScreenSize(float& height, float& width);

    HFont* CreateFont(const char* font, int size, int flags);
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