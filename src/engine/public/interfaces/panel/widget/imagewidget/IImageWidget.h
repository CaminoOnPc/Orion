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

    void SetSize(float height, float width);
    void GetSize(float& height, float& width);

    void SetImage(const char* image);
    void GetImage(const char*& image);

    void SetColor(Color color);
    void GetColor(Color& color);

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
    wiSprite* m_Widget;
};