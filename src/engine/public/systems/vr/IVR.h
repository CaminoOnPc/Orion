/*
    File: IVR.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include <openvr.h>

#include <wiGraphicsDevice.h>

#pragma comment(lib, "openvr_api.lib")

class IInterfaces;

class IObject;

class IVR
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IVR initalization process
    void Start(IInterfaces* interfaces);

    // Activates IVR shutdown process
    void Stop();

    // Processing a single frame of IVR
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
    uint32_t m_RenderWidth;
    uint32_t m_RenderHeight;

    vr::IVRSystem* m_IVRSystem;
    vr::IVRRenderModels* m_IVRModels;

    char m_rDevClassChar[vr::k_unMaxTrackedDeviceCount];

    std::string m_strPoseClasses;
    vr::HmdMatrix34_t m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];
    vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];

    int m_iValidPoseCount;
    int m_iValidPoseCount_Last;

    bool g_ActivateVr;
public:
    wiGraphics::Texture* m_RenderTargetLeft;
    wiGraphics::Texture* m_RenderTargetRight;
};