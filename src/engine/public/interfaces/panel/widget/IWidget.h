/*
    File: IWidget.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../HFont.h"
    
class IEditField;

class HFont;

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

    enum EWidgetFlags
    {
        WIDGETFLAGS_IDLE,
        FONTFLAGS_FOCUSED = 0x001,
    };

    enum EFontFlags
    {
        FONTFLAGS_NONE,
        FONTFLAGS_SHADOW = 0x001,
        FONTFLAGS_OUTLINE = 0x002,
    };

    void SetScreenSize(float height, float width);
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
    std::vector<IEditField*> m_EditFields;
};