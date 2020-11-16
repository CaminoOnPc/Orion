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

    void SetPos(float x, float y, bool immedUpdate = true);
    void GetPos(float& x, float& y);

    void SetSize(int size, bool immedUpdate = true);
    void GetSize(int& size);

    void SetHidden(bool hidden, bool immedUpdate = true);
    void GetHidden(bool& hidden);

    void SetText(std::string text, bool immedUpdate = true);
    void GetText(std::string& text);

    void SetColor(Color color, bool immedUpdate = true);
    void GetColor(Color& color);

    void SetFont(HFont* font, bool immedUpdate = true);
    void GetFont(HFont*& font);

    void SetPriority(int priority, bool immedUpdate = true);
    void GetPriority(int& priority);

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
    wiSpriteFont* m_Widget;
public:
    struct EWidgetData
    {
        std::string m_Text;
        Vector m_Position;
        Color m_Color;
        int m_Size;

        HFont* m_Font;
        int m_Priority;
        bool m_Hidden;
    };

    EWidgetData m_Data;
};