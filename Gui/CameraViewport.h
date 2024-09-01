#pragma once

// #include <nfx/GUI/Combo.h>
// #include <nfx/GUI/CheckBox.h>
//
// #include "VideoCapture/VideoCaptureDevice.h"
//
// #include <nfx/Graphics/GL/Definitions.h>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include <nfx/Graphics/GL/Definitions.h>

class CameraViewport final
{
public:
	CameraViewport();
	// CameraViewport() = delete;
	CameraViewport(const CameraViewport&) = delete;
	CameraViewport& operator=(const CameraViewport&) = delete;
	CameraViewport(CameraViewport&&) = delete;
	CameraViewport& operator=(CameraViewport&&) = delete;
	~CameraViewport();

	void draw();

public:
	void setFrame(const cv::Mat& frame);

private:
	GLuint imageTexture_cam0;

	cv::Mat m_frame;

	void BindCVMat2GLTexture(const cv::Mat& frame);
	void initTexture(const cv::Mat& frame);
};
