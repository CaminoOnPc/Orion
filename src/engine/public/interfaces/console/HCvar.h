/*
    File: HCvar.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <Includes.h>

class HCvar
{
public:
    HCvar(const char* command);
    ~HCvar();

    struct ECvarData
    {
        const char* m_Command;
        const char* m_Value;
        float m_FloatValue;
        int m_IntValue;
    };

    ECvarData m_Cvar;
protected:
    template <class T> void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            *ppT = nullptr;
        }
    }
};