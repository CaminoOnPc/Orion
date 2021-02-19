/*
	File: IVR.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IVR.h"

//-----------------------------------------------------------------------------
// Activates IVR initalization process
//-----------------------------------------------------------------------------
void IVR::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	vr::EVRInitError eError = vr::VRInitError_None;
	m_IVRSystem = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		SafeRelease(&m_IVRSystem);
		char buf[1024];
		sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		std::cout << "[ERROR] IInterfaces::IVR::OpenVR error Initalizing OpenVR(eError) " << buf << std::endl;
	}

	m_IVRSystem->GetRecommendedRenderTargetSize(&m_RenderWidth, &m_RenderHeight);

	m_IVRModels = (vr::IVRRenderModels*)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);
	if (!m_IVRModels)
	{
		SafeRelease(&m_IVRSystem);
		vr::VR_Shutdown();

		char buf[1024];
		sprintf_s(buf, ARRAYSIZE(buf), "Unable to get render model interface: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		std::string temp(buf);
		std::wstring wtemp(temp.begin(), temp.end());
		std::cout << "[ERROR] IInterfaces::IVR::OpenVR error Initalizing OpenVR(eModels) " << buf << std::endl;
	}

	if (!vr::VRCompositor())
	{
		std::cout << "[ERROR] IInterfaces::IVR::OpenVR error Initalizing OpenVR(eCompositor) " << std::endl;
	}
}

//-----------------------------------------------------------------------------
// Activates IVR shutdown process
//-----------------------------------------------------------------------------
void IVR::Stop()
{
	vr::VR_Shutdown();

	SafeRelease(&m_Interface);
}

//-----------------------------------------------------------------------------
// Processing a single frame of IVR
//-----------------------------------------------------------------------------
void IVR::Run(float dt)
{
	if (!m_Interface->m_Tier0->m_VR->m_IVRSystem)
	{
		std::cout << "[ERROR] IInterfaces::IDirectX11 cant find VRSystem" << std::endl;
		return;
	}

	/*
	wiGraphics::GraphicsDevice* device = wiRenderer::GetDevice();
	if (device)
	{
		wiGraphics::TextureDesc* textureDesc = new wiGraphics::TextureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));

		textureDesc->Width = m_RenderWidth;
		textureDesc->Height = m_RenderHeight;
		textureDesc->MipLevels = 1;
		textureDesc->ArraySize = 1;
		textureDesc->Format = wiGraphics::FORMAT::FORMAT_R8G8B8A8_UNORM;
		textureDesc->SampleCount = 1;
		textureDesc->Usage = wiGraphics::USAGE::USAGE_DEFAULT;
		textureDesc->BindFlags = wiGraphics::BIND_RENDER_TARGET | wiGraphics::BIND_SHADER_RESOURCE;
		textureDesc->CPUAccessFlags = 0;
		textureDesc->MiscFlags = 0;

		device->CreateTexture(textureDesc, NULL, m_RenderTargetLeft);
		device->CreateTexture(textureDesc, NULL, m_RenderTargetRight);

		device->CreateSubresource(m_RenderTargetLeft, wiGraphics::SUBRESOURCE_TYPE::RTV, 0, 1, 0, 1);
		device->CreateSubresource(m_RenderTargetRight, wiGraphics::SUBRESOURCE_TYPE::RTV, 0, 1, 0, 1);

		device->CreateSubresource(m_RenderTargetLeft, wiGraphics::SUBRESOURCE_TYPE::SRV, 0, 1, 0, 1);
		device->CreateSubresource(m_RenderTargetRight, wiGraphics::SUBRESOURCE_TYPE::SRV, 0, 1, 0, 1);
	}

	const vr::Texture_t vrTexture[2] =
	{
		{ buffer, vr::TextureType_DirectX, vr::ColorSpace_Gamma },
		{ buffer, vr::TextureType_DirectX, vr::ColorSpace_Gamma }
	};

	const vr::VRTextureBounds_t vrTextureBounds[2] =
	{
		{ 0.0f, 0.0f, 0.5f, 1.0f },
		{ 0.5f, 0.0f, 1.0f, 1.0f }
	};

	vr::VRCompositor()->Submit(vr::Eye_Left, &vrTexture[0], &vrTextureBounds[0], vr::Submit_Default);
	vr::VRCompositor()->Submit(vr::Eye_Right, &vrTexture[1], &vrTextureBounds[1], vr::Submit_Default);

	vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	m_iValidPoseCount = 0;
	m_strPoseClasses = "";
	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_rTrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_iValidPoseCount++;
			m_rmat4DevicePose[nDevice] = m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking;
			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (m_Interface->m_Tier0->m_VR->m_IVRSystem->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:        m_rDevClassChar[nDevice] = 'C'; break;
				case vr::TrackedDeviceClass_HMD:               m_rDevClassChar[nDevice] = 'H'; break;
				case vr::TrackedDeviceClass_Invalid:           m_rDevClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_GenericTracker:    m_rDevClassChar[nDevice] = 'O'; break;
				case vr::TrackedDeviceClass_TrackingReference: m_rDevClassChar[nDevice] = 'T'; break;
				default:                                       m_rDevClassChar[nDevice] = '?'; break;
				}
			}
			m_strPoseClasses += m_rDevClassChar[nDevice];
		}
	}

	if (m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{

	}
	*/
}