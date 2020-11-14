/*
    File: ITextWidget.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class HFont;

class IInterfaces;

class ITextWidget
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates ITextWidget initalization process
    void Start(IInterfaces* interfaces);

    // Activates ITextWidget shutdown process
    void Stop();

    // Processing a single frame of ITextWidget
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void SetPos(float x, float y);
    void GetPos(float& x, float& y);

    void SetSize(int size);
    void GetSize(int& size);

    void SetText(const char* text);
    void GetText(const char*& text);

    void SetFont(HFont* font);
    void GetFont(HFont*& font);

    void Update();

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
    RenderPath2D* m_RenderPath;
    wiSpriteFont* m_Widget;
public:
    HFont* m_Font;
};