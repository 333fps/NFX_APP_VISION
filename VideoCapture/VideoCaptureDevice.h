#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include "nfx/VideoCapture/VideoResolution.h"

class VideoCaptureDevice final
{
public:
	explicit VideoCaptureDevice(uint16_t hardwareIndex);
	VideoCaptureDevice() = delete;
	VideoCaptureDevice(const VideoCaptureDevice&) = delete;
	VideoCaptureDevice& operator=(const VideoCaptureDevice&) = delete;
	VideoCaptureDevice(VideoCaptureDevice&&) = delete;
	VideoCaptureDevice& operator=(VideoCaptureDevice&&) = delete;
	~VideoCaptureDevice();

	bool open(uint16_t width = 640, uint16_t height = 480, uint16_t fps = 30);
	bool open(const nfx::VideoResolution& p_VideoResolution);
	void close();
	bool isOpen() const;

	float fps() const;

	void registerFrameReadyCallback(std::function<void(const cv::Mat&)> p_frameReadyCallback);

private:
	void onFrameReady() const;

private:
	uint16_t m_hardwareIndex;
	cv::Mat m_frame;
	cv::VideoCapture m_videoCapture;

	void aquireFrame(std::stop_token token);
	std::jthread jt;

	float m_fps{ 0.f };

	std::vector<std::function<void(const cv::Mat&)>> m_frameReadyCallbacks;
};
