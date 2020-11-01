/*
    File: HFont.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <Includes.h>

class HFont
{
public:
    HFont(const char* font, int size, int flags);
    ~HFont();

    struct EFontData
    {
        wchar_t* m_Name;
        int m_Size;
        int m_Flag;
    };

    EFontData m_Font;
protected:
    template <class T> void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            *ppT = nullptr;
        }
    }

    wchar_t* m_Name;
};