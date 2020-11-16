/*
    File: IGradientWidget.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class IGradientWidget
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IGradientWidget initalization process
    void Start(IInterfaces* interfaces);

    // Activates IGradientWidget shutdown process
    void Stop();

    // Processing a single frame of IGradientWidget
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void SetPos(float x, float y, bool immedUpdate = true);
    void GetPos(float& x, float& y);

    void SetSize(float width, float height, bool immedUpdate = true);
    void GetSize(float& width, float& height);

    void SetHidden(bool hidden, bool immedUpdate = true);
    void GetHidden(bool& hidden);

    void SetColor(Color start, Color end, bool immedUpdate = true);
    void GetColor(Color& start, Color& end);

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
public:
    std::vector<wiSprite*> m_Widgets;
public:
    struct EWidgetData
    {
        Vector m_Position;
        Vector m_Size;
        Color m_Start;
        Color m_End;

        bool m_Hidden;
    };

    EWidgetData m_Data;
};