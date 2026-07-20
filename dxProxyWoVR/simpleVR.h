
#pragma once
#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
// Windows Header Files
#include <windows.h>
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <iostream>
#include <sstream>
#include "stCommon.h"

#include <openvr.h>
#include <vector>

class simpleVR
{
	vr::IVRSystem* openVRSession = nullptr;
	vr::IVRChaperone* openVRChaperone = nullptr;
	vr::IVRRenderModels* openVRModels = nullptr;
	vr::TrackedDevicePose_t rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	bool _isConnected = false;
	POINT bufferSize;
	uMatrix projMatrixRaw[2];
	uMatrix eyeViewMatrixRaw[2];
	uMatrix eyeViewMatrix[2];
	uMatrix identMatrix;
	uMatrix hmdMatrix;
	uMatrix controllerMatrix[4];
	bool printLogs = false;
	std::stringstream logError;
	vr::HmdVector2_t depthRange;
	vr::VRTextureBounds_t textureBounds[2];
	bool asymmetricProjection = true;

private:
	void InitalizeVR();
	std::vector<float> m_frameIntervals;
	uint32_t m_perfLogFrameCount = 0;
	uint32_t m_startDroppedFrames = 0;
	uint32_t m_startFramePresents = 0;
	uint32_t m_reprojectionCount = 0;
	bool m_perfLogStarted = false;
	void UpdatePerfLogging();

public:
	simpleVR(bool showLogs = false);
	~simpleVR();

	bool PreloadVR();
	bool StartVR();
	bool StopVR();
	bool isEnabled();
	void Recenter();
	POINT GetBufferSize();
	void SetProjection(vr::HmdVector2_t depth);
	void SetActionPose(vr::HmdMatrix34_t matPose, poseType poseType);
	void SetFramePose();
	uMatrix GetFramePose(poseType poseType, int eye);
	void Render(ID3D11Texture2D* leftEye, ID3D11Texture2D* leftDepth, ID3D11Texture2D* rightEye, ID3D11Texture2D* rightDepth);
	void WaitGetPoses();
	void MakeIPDOffset();
	bool HasErrors();
	std::string GetErrors();

	float cfg_ipdOffset = 0.0f;
};
