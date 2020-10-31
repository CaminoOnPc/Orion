/*
    File: WinMain.cpp
    Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "WinMain.h"
#include "stdafx.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#ifdef DEBUG
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    freopen("CON", "w", stdout);
#endif // DEBUG

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
            m_Base->EOnFrame();
		}
	}

    m_Base->EOnFinish();
    m_Base = nullptr;
}