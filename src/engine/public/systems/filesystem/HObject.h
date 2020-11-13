/*
    File: HObject.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <Includes.h>

class HObject
{
public:
    HObject();
    ~HObject();

    std::string m_ModelName;
    std::string m_ModelPath;
protected:
    template <class T> void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            *ppT = nullptr;
        }
    }
};