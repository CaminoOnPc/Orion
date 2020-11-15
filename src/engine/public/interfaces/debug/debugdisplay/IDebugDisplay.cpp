/*
	File: IDebugDisplay.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IDebugDisplay.h"

//-----------------------------------------------------------------------------
// Activates IDebugCamera initalization process
//-----------------------------------------------------------------------------
void IDebugDisplay::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	// wiProfiler::SetEnabled(true);

	QueryPerformanceFrequency((LARGE_INTEGER*)&m_Frequency);
	if (m_Frequency == 0)
	{
		return;
	}

	m_TicksTime = (float)(m_Frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_Time);

	m_GpuData.m_CanReadGpu = true;
	m_CpuData.m_CanReadCpu = true;

	m_GpuData.m_GpuTick = timeGetTime();

	PDH_STATUS status = PdhOpenQuery(NULL, 0, &m_CpuData.m_QueryHandle);
	if (status != ERROR_SUCCESS)
	{
		m_CpuData.m_CanReadCpu = false;
	}

	status = PdhAddCounter(m_CpuData.m_QueryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_CpuData.m_CounterHandle);
	if (status != ERROR_SUCCESS)
	{
		m_CpuData.m_CanReadCpu = false;
	}

	m_CpuData.m_CpuTick = GetTickCount();

	HFont* font = m_Interface->m_Tier2->m_IWidget->CreateFont("Arame-Mono.ttf", 24, IWidget::EFontFlags::FONTFLAGS_OUTLINE);

	std::string pos;
	pos.append("POS: ");
	pos.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Position.x));
	pos.append(" ");
	pos.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Position.y));
	pos.append(" ");
	pos.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Position.z));

	m_PositionText = new ITextWidget();
	m_PositionText->Start(m_Interface);

	m_PositionText->SetFont(font);
	m_PositionText->SetText(pos);
	
	m_PositionText->SetPos(10, 10);

	std::string rot;
	rot.append("ROT: ");
	rot.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Rotation.x));
	rot.append(" ");
	rot.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Rotation.y));
	rot.append(" ");
	rot.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Rotation.z));

	m_RotationText = new ITextWidget();
	m_RotationText->Start(m_Interface);

	m_RotationText->SetFont(font);
	m_RotationText->SetText(rot);

	m_RotationText->SetPos(10, 30);

	std::string fps;
	fps.append(std::to_string(m_Fps));
	fps.append(" ");
	fps.append(" +- ");
	fps.append(Utils::string_round(m_DeltaTime));
	fps.append("ms");

	m_FpsText = new ITextWidget();
	m_FpsText->Start(m_Interface);

	m_FpsText->SetFont(font);
	m_FpsText->SetText(fps);

	m_FpsText->SetPos((m_Interface->m_Base->m_Settings->m_width / 2) + 150, 10);
	m_FpsText->SetColor(Color(255, 255, 0));

	std::string serverCpu;
	serverCpu.append(std::to_string(m_CpuUsage));
	serverCpu.append("% server CPU");

	m_ServerCpuText = new ITextWidget();
	m_ServerCpuText->Start(m_Interface);

	m_ServerCpuText->SetFont(font);
	m_ServerCpuText->SetText(serverCpu);

	m_ServerCpuText->SetPos((m_Interface->m_Base->m_Settings->m_width / 2) + 150, 30);
		
	std::string clientCpu;
	clientCpu.append(std::to_string(m_CpuUsage));
	clientCpu.append("% client CPU");

	m_ClientCpuText = new ITextWidget();
	m_ClientCpuText->Start(m_Interface);

	m_ClientCpuText->SetFont(font);
	m_ClientCpuText->SetText(clientCpu);

	m_ClientCpuText->SetPos((m_Interface->m_Base->m_Settings->m_width / 2) + 150, 50);

	std::string worldName;
	worldName.append(m_Interface->m_Tier2->m_IWorld->m_WorldName);

	m_WorldNameText = new ITextWidget();
	m_WorldNameText->Start(m_Interface);

	m_WorldNameText->SetFont(font);
	m_WorldNameText->SetText(worldName);

	m_WorldNameText->SetPos((m_Interface->m_Base->m_Settings->m_width / 2) + 150, 70);
}

//-----------------------------------------------------------------------------
// Activates IDebugDisplay shutdown process
//-----------------------------------------------------------------------------
void IDebugDisplay::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IDebugCamera
//-----------------------------------------------------------------------------
void IDebugDisplay::Run(float dt)
{
	INT64 time;

	QueryPerformanceCounter((LARGE_INTEGER*)&time);

	float timeDifference = (float)(time - m_Time);

	m_DeltaTime = timeDifference / m_TicksTime;

	m_Time = time;

	m_GpuData.m_GpuTickCount++;

	if (timeGetTime() >= (m_GpuData.m_GpuTick + 1000))
	{
		m_Fps = m_GpuData.m_GpuTickCount;
		m_GpuData.m_GpuTickCount = 0;

		m_GpuData.m_GpuTick = timeGetTime();
	}

	PDH_FMT_COUNTERVALUE value;

	if (m_CpuData.m_CanReadCpu)
	{
		if ((m_CpuData.m_CpuTick + 1000) < GetTickCount())
		{
			m_CpuData.m_CpuTick = GetTickCount();

			PdhCollectQueryData(m_CpuData.m_QueryHandle);

			PdhGetFormattedCounterValue(m_CpuData.m_CounterHandle, PDH_FMT_LONG, NULL, &value);

			m_CpuUsage = value.longValue;
		}
	}

	std::string pos;
	pos.append("pos: ");
	pos.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Position.x));
	pos.append(" ");
	pos.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Position.y));
	pos.append(" ");
	pos.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Position.z));
	m_PositionText->SetText(pos);

	std::string rot;
	rot.append("rot: ");
	rot.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Rotation.x));
	rot.append(" ");
	rot.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Rotation.y));
	rot.append(" ");
	rot.append(Utils::string_round(m_Interface->m_Tier3->m_IGame->m_DebugCamera->m_Camera->m_Rotation.z));
	m_RotationText->SetText(rot);

	std::string fps;
	fps.append(std::to_string(m_Fps));
	fps.append(" ");
	fps.append(" +- ");
	fps.append(Utils::string_round(m_DeltaTime));
	fps.append("ms");
	m_FpsText->SetText(fps);

	std::string serverCpu;
	serverCpu.append(std::to_string(m_CpuUsage));
	serverCpu.append("% server CPU");
	m_ServerCpuText->SetText(serverCpu);

	std::string clientCpu;
	clientCpu.append(std::to_string(m_CpuUsage));
	clientCpu.append("% client CPU");
	m_ClientCpuText->SetText(clientCpu);

	std::string worldName;
	worldName.append(m_Interface->m_Tier2->m_IWorld->m_WorldName);
	m_WorldNameText->SetText(worldName);
}