/*
	File: IBase.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IBase.h"

#include "../../common/WinMain.h"

IBase* m_Base;

//-----------------------------------------------------------------------------
// Activates IBase initalization process
//-----------------------------------------------------------------------------
bool IBase::EOnInit(HINSTANCE instance)
{
    m_Settings = new ISettings;
    if (!m_Settings)
    {
        return false;
    }

    m_Settings->Start(NULL);

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = instance;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = L"Orion";
	ATOM a = RegisterClassEx(&wcex);

	RECT r = { 0, 0, m_Settings->m_width, m_Settings->m_height };
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);

	HWND hWnd = CreateWindow(
		(LPCWSTR)a,
		L"Project Orion",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		r.right - r.left,
		r.bottom - r.top,
		NULL,
		NULL,
		instance,
		NULL);

    wiPlatform::GetWindowState().window = hWnd;
    wiPlatform::InitDPI();

	ShowWindow(hWnd, true);

	m_Interfaces = new IInterfaces;
	if (!m_Interfaces)
	{
		return false;
	}

	m_Interfaces->m_HInstance = instance;

	if (!m_Interfaces->EOnInit(this));
	{
		return false;
	}

	m_Settings->Start(m_Interfaces);

	return true;
}

//-----------------------------------------------------------------------------
// Activates IBase shutdown process
//-----------------------------------------------------------------------------
bool IBase::EOnFinish()
{
	if (m_Interfaces->EOnFinish())
	{
		SafeRelease(&m_Interfaces);
	}

	return true;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IBase
//-----------------------------------------------------------------------------
void IBase::EOnUpdate(float dt)
{
	m_Interfaces->EOnUpdate(dt);
}

//-----------------------------------------------------------------------------
// Processing a single frame of IBase
//-----------------------------------------------------------------------------
void IBase::EOnFrame(float dt)
{
	m_Interfaces->EOnFrame(dt);
}

//-----------------------------------------------------------------------------
// WndProc event handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    switch (umessage)
    {
    case WM_CHAR:
    {
        switch (lparam)
        {
        case VK_BACK:
        {
            if (wiBackLog::isActive())
            {
                wiBackLog::deletefromInput();
            }

            wiTextInputField::DeleteFromInput();
        }
        break;

        default:
        {
            const char c = (const char)(TCHAR)wparam;
            if (wiBackLog::isActive())
            {
                wiBackLog::input(c);
            }

            wiTextInputField::AddInput(c);

            for (size_t i = 0; i < m_Base->m_Interfaces->m_Tier2->m_IWidget->m_EditFields.capacity(); i++)
            {
                IEditField* editField = m_Base->m_Interfaces->m_Tier2->m_IWidget->m_EditFields[i];
                if (editField)
                {
                    if (editField->m_Flags & IWidget::EWidgetFlags::FONTFLAGS_FOCUSED)
                    {
                        if (!wiInput::Press(wiInput::KEYBOARD_BUTTON_BACKSPACE))
                        {
                            
                        }
                    }
                }
            }
        }
        break;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
    }
    break;

    case WM_SIZE:
    {
        wiEvent::FireEvent(SYSTEM_EVENT_CHANGE_RESOLUTION, lparam);
    }
    break;

    case WM_DPICHANGED:
    {
        wiEvent::FireEvent(SYSTEM_EVENT_CHANGE_DPI, lparam);
    }
    break;

    case WM_INPUT:
    {
        wiRawInput::ParseMessage((void*)lparam);
    }
    break;

    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;

    case WM_CLOSE:
    {
        PostQuitMessage(0);
    }
    break;
    }

    return DefWindowProc(hwnd, umessage, wparam, lparam);
}