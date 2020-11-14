/*
    File: IConsole.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../HCvar.h"

class IImageWidget;
class ITextWidget;
class HCvar;

class IInterfaces;

class IConsole
{
public:
    // * Those are calls allocated for class initialization and running
    // ---------------------------------------------

    // Activates IConsole initalization process
    void Start(IInterfaces* interfaces);

    // Activates IConsole shutdown process
    void Stop();

    // Processing a single frame of IConsole
    void Run(float dt);

    // * Those are calls that are accessible by everyone 
    // ---------------------------------------------

    void ExecuteCommand(const char* command, const char* args);
    void ExecuteCommand(const char* command, float args);
    void ExecuteCommand(const char* command, int args);

    void InternalExecuteCommand(const char* command, const char* args, float fargs, int iargs);
    void LogCommand(const char* text);
public:
    void Callback_r_vsync(int value);   
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
    std::vector< HCvar* > m_Cvars;
public:
    HCvar* r_vsync;
public:
    bool m_Active;

    ITextWidget* m_OutputText;
    ITextWidget* m_InputText;
    IImageWidget* m_Background;
    IImageWidget* m_Input;

   

    std::string m_FirstOutput;
    std::string m_Output;
    int m_Lines;
};