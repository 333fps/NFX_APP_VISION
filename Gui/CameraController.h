#pragma once

#include <nfx/GUI/Combo.h>
#include <nfx/GUI/CheckBox.h>

// #include "VideoCapture/VideoCaptureDevice.h"
#include <nfx/VideoCapture/VideoCaptureDevice.h>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include "CameraViewport.h"

class CameraController final
{
public:
	CameraController(CameraViewport* p_cameraViewport);
	CameraController() = delete;
	CameraController(const CameraController&) = delete;
	CameraController& operator=(const CameraController&) = delete;
	CameraController(CameraController&&) = delete;
	CameraController& operator=(CameraController&&) = delete;
	~CameraController();

	void draw();

private:
	std::unique_ptr<nfx::VideoCaptureDevice> m_videoCaptureDevice;

	nfx::GUI::Combo m_cbCameras;
	nfx::GUI::Combo m_cbResolutions;

	nfx::GUI::CheckBox m_checkBox;

private:
	void cameraIndexChanged(unsigned);
	void cameraCheckBoxClicked(bool);

private:
	CameraViewport* m_cameraViewport;
};
