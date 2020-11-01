/*
    File: ISurface.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../HFont.h"
    
class IInterfaces;

class ISurface
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates ISurface initalization process
    void Start(IInterfaces* interfaces);

    // Activates ISurface shutdown process
    void Stop();

    // Processing a single frame of ISurface
    void Run();

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void StartFrame();
    void EndFrame();

    enum EFontFlags
    {
        FONTFLAGS_NONE,
        FONTFLAGS_OUTLINE = 0x001,
    };

    HFont* CreateFont(const char* font, int size, int flags);

    void DrawText(HFont* font, const char* text, int x, int y, Color color);
    void DrawText(HFont* font, const char* text, int x, int y, int flags, Color color);

    void DrawRect(int x, int y, float w, float h, Color color);
    void DrawRect(int x, int y, float w, float h, bool outline, Color color);

    void DrawLine(int x0, int y0, int x1, int y1, Color color);
    void DrawLine(int x0, int y0, int x1, int y1, float width, Color color);

    void DrawBitmap(const char* image, int x, int y, float w, float h, float alpha);

protected:
    IInterfaces* m_Interface;
};