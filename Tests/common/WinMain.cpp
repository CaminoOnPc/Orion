/*
    File: WinMain.cpp
    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "WinMain.h"
#include "stdafx.h"

float g_TicksTime;

INT64 g_Frequency;
INT64 g_Time;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#ifdef DEVELOPER
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen("CON", "w", stdout);
#endif // DEVELOPER

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    BOOL dpi_success = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    assert(dpi_success);

    wiStartupArguments::Parse(lpCmdLine);

    m_hInstance = hInstance;
    m_hPrevInstance = hPrevInstance;

    m_Base = new IBase;
    if (!m_Base)
    {
        return 0;
    }

    m_Base->EOnInit(m_hInstance);

    QueryPerformanceFrequency((LARGE_INTEGER*)&g_Frequency);

    g_TicksTime = (float)(g_Frequency / 1000);

    QueryPerformanceCounter((LARGE_INTEGER*)&g_Time);

    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
        {
            INT64 time;

            QueryPerformanceCounter((LARGE_INTEGER*)&time);

            float timeDifference = (float)(time - g_Time);

            g_Time = time;

            m_Base->EOnFrame(timeDifference / g_TicksTime);
		}
	}

    m_Base->EOnFinish();
    m_Base = nullptr;
}