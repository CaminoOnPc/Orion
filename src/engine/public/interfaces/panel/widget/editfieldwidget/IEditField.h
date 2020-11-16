/*
    File: IEditField.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class IEditField
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IEditField initalization process
    void Start(IInterfaces* interfaces);

    // Activates IEditField shutdown process
    void Stop();

    // Processing a single frame of IEditField
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void SetPos(float x, float y, bool immedUpdate = true);
    void GetPos(float& x, float& y);

    void SetSize(float width, float height, bool immedUpdate = true);
    void GetSize(float& width, float& height);

    void SetHidden(bool hidden, bool immedUpdate = true);
    void GetHidden(bool& hidden);

    void SetText(std::string text, bool immedUpdate = true);
    void GetText(std::string& text);

    void SetColor(Color color, bool immedUpdate = true);
    void GetColor(Color& color);

    void SetFont(HFont* font, bool immedUpdate = true);
    void GetFont(HFont*& font);

    void SetEvent(std::function<void(const char*)> callback);
    void SetInput(const char* text);

    void SetPriority(int priority, bool immedUpdate = true);
    void GetPriority(int& priority);

    void Update(float dt);
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
    wiSpriteFont* m_EditWidget;
    wiSprite* m_Widget;
    Hitbox2D m_HitBox;

    XMFLOAT2 m_PointerPosition = XMFLOAT2(0, 0);
    Hitbox2D m_PointerHitBox;

    int m_Flags;
public:
    struct EEditData
    {
        std::string m_Text;
        Vector m_Position;
        Color m_Color;
        int m_Size;

        HFont* m_Font;
        bool m_Hidden;
    };

    EEditData m_EditData;

    struct EWidgetData
    {
        Vector m_Position;
        Vector m_Size;
        Color m_Color;

        int m_Priority;
        bool m_Hidden;
    };

    EWidgetData m_Data;

    std::function<void(const char*)> m_Callback;
};