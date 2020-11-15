/*
    File: IDebugDisplay.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class ICamera;

class IInterfaces;

class IDebugDisplay
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IDebugDisplay initalization process
    void Start(IInterfaces* interfaces);

    // Activates IDebugDisplay shutdown process
    void Stop();

    // Processing a single frame of IDebugDisplay
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

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
    struct EGPUData
    {
        bool m_CanReadGpu;

        int m_GpuTickCount;
        unsigned long m_GpuTick;
    };

    EGPUData m_GpuData;

    struct ECPUData
    {
        bool m_CanReadCpu;

        HCOUNTER m_CounterHandle;
        HQUERY m_QueryHandle;

        unsigned long m_CpuTick;
    };

    ECPUData m_CpuData;

    float m_TicksTime;
    float m_DeltaTime;

    INT64 m_Frequency;
    INT64 m_Time;
public:
    int m_Fps;

    long m_GpuUsage;
    long m_CpuUsage;
public:
    ITextWidget* m_FpsText;

    ITextWidget* m_ServerCpuText;
    ITextWidget* m_ClientCpuText;

    ITextWidget* m_WorldNameText;
public:
    ITextWidget* m_PositionText;
    ITextWidget* m_RotationText;
};