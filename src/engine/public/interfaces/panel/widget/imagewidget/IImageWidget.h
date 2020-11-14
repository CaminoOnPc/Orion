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

    void SetPos(float x, float y);
    void GetPos(float& x, float& y);

    void SetSize(float width, float height);
    void GetSize(float& width, float& height);

    void SetHidden(bool hidden);
    void GetHidden(bool& hidden);

    void SetImage(const char* image);
    void GetImage(const char*& image);

    void SetColor(Color color);
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
    Color m_Color;

    Vector m_Position;
    Vector m_Size;

    const char* m_Image;

    bool m_Hidden;
};