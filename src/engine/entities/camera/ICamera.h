/*
    File: ICamera.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

class IInterfaces;

class ICamera
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates ICamera initalization process
    void Start(IInterfaces* interfaces);

    // Activates ICamera shutdown process
    void Stop();

    // Processing a single frame of ICamera
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

protected:
    IInterfaces* m_Interface;
public:
    XMFLOAT3 m_Forward;
    XMFLOAT3 m_Right;
    XMFLOAT3 m_Up;
public:
    bool m_IsActive;

    // Camera coordinates
    Vector m_Position;
    Vector m_Rotation;

    // Camera view
    float m_ViewAspectRatio;
    float m_ViewDistance;
    float m_ViewFov;

    float m_Near;
    float m_Far;
};