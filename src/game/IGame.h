/*
    File: IGame.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../engine/public/interfaces/debug/debugdisplay/IDebugDisplay.h"
#include "../engine/public/interfaces/debug/debugcamera/IDebugCamera.h"

#include "../engine/public/interfaces/panel/widget/imagewidget/IImageWidget.h"
#include "../engine/public/interfaces/panel/widget/textwidget/ITextWidget.h"


class IImageWidget;
class ITextWidget;

class IDebugDisplay;
class IDebugCamera;

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
    void Run(float dt);

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
    IDebugDisplay* m_DebugDisplay;
    IDebugCamera* m_DebugCamera;
public:
    wiSprite m_UI;
};