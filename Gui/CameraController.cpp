#include "CameraController.h"

#include <nfx/VideoCapture/VideoCaptureDeviceInfo.h>
#include <nfx/VideoCapture/VideoResolution.h>

#include <imgui.h>
#include <implot.h>

CameraController::CameraController(CameraViewport* p_cameraViewport) : m_cameraViewport{ p_cameraViewport }
{
	auto videoDeviceInfoList = nfx::VideoCaptureDeviceInfo::availableVideoDevices();
	videoDeviceInfoList.sort();

	unsigned i{ 0 };
	for (const auto& device : videoDeviceInfoList)
	{
		m_cbCameras.addItem(device.name());

		m_cbCameras.setData(i, device.resolutions());

		++i;
	}

	m_cbCameras.registerIndexChangeCallback(std::bind(&CameraController::cameraIndexChanged, this, std::placeholders::_1));
	m_checkBox.registerStateChangeCallback(std::bind(&CameraController::cameraCheckBoxClicked, this, std::placeholders::_1));
}

CameraController::~CameraController()
{
}

void CameraController::draw()
{
	if (ImGui::Begin("Camera controller", nullptr))
	{
		m_cbCameras.draw();
		m_cbResolutions.draw();
		m_checkBox.draw();

		float fps{ 0.f };
		if (m_videoCaptureDevice)
		{
			fps = m_videoCaptureDevice->fps();
		}
		ImGui::Text("CameraFPS %.2f ", fps);
	}
	ImGui::End();
}

void CameraController::cameraIndexChanged(unsigned idx)
{
	m_cbResolutions.clear();

	const auto& data = std::any_cast<const std::vector<nfx::VideoResolution>&>(m_cbCameras.data(idx));
	for (const auto& res : data)
	{
		std::stringstream ss;
		ss << res.x << "x" << res.y << "/" << res.bitcount << "bpp @" << res.fps << "fps ";

		m_cbResolutions.addItem(ss.str());
	}
}

void CameraController::cameraCheckBoxClicked(bool b)
{
	if (b)
	{
		m_videoCaptureDevice.reset(new nfx::VideoCaptureDevice{ (uint16_t)m_cbCameras.currentIndex() });

		const auto& data = std::any_cast<const std::vector<nfx::VideoResolution>&>(m_cbCameras.data(m_cbCameras.currentIndex()));
		const auto& resolution = data.at(m_cbResolutions.currentIndex());

		m_videoCaptureDevice->open(resolution.x, resolution.y, resolution.fps);

		m_videoCaptureDevice->registerFrameReadyCallback(
			std::bind(
				&CameraViewport::setFrame,
				m_cameraViewport,
				std::placeholders::_1));
	}
	else
	{
		m_videoCaptureDevice->close();
		// m_videoCaptureDevice.reset();
	}
}