/*
    File: IConsole.h

    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#include <IInterfaces.h>
#include <Includes.h>

#include "../HCvar.h"

class IEditField;
class IGradientWidget;
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
    void ProcessCommand(const char* command);

    void InternalExecuteCommand(const char* command, const char* args, float fargs, int iargs);
    void LogCommand(const char* text);
public:
    void Callback_mat_vsync(int value);   
    void Callback_mat_mode(int value);
    void Callback_clear();
    void Callback_quit();
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
    HCvar* sv_vectest;

    HCvar* cl_showfps;
    HCvar* cl_showpos;

    HCvar* mat_vsync;
    HCvar* mat_mode;
    HCvar* clear;
    HCvar* quit;
public:
    std::vector< HCvar* > m_Cvars;
public:
    ITextWidget* m_TitleWidget;

    IGradientWidget* m_BackgroundWidget;
    IGradientWidget* m_HeaderWidget;

    ITextWidget* m_OutputWidget;
    IEditField* m_InputWidget;
public:
    bool m_Active;
 
    std::string m_FirstOutput;
    std::string m_Output;
    int m_Lines;
};