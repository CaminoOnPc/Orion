/*
    File: IImageWidget.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class IImageWidget
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IImageWidget initalization process
    void Start(IInterfaces* interfaces);

    // Activates IImageWidget shutdown process
    void Stop();

    // Processing a single frame of IImageWidget
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void SetPos(float x, float y, bool immedUpdate = true);
    void GetPos(float& x, float& y);

    void SetSize(float width, float height, bool immedUpdate = true);
    void GetSize(float& width, float& height);

    void SetHidden(bool hidden, bool immedUpdate = true);
    void GetHidden(bool& hidden);

    void SetImage(std::string image, bool immedUpdate = true);
    void GetImage(std::string& image);

    void SetColor(Color color, bool immedUpdate = true);
    void GetColor(Color& color);

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
    wiSprite* m_Widget;
public:
    struct EWidgetData
    {
        std::string m_Image;
        Vector m_Position;
        Vector m_Size;
        Color m_Color;

        bool m_Hidden;
    };

    EWidgetData m_Data;
};