#pragma once

#include <nfx/GUI.h>



#include <nfx/VideoCapture.h>

class CameraViewport final : public nfx::GUI::Window
{
public:
	CameraViewport();
	CameraViewport(const CameraViewport&) = delete;
	CameraViewport& operator=(const CameraViewport&) = delete;
	CameraViewport(CameraViewport&&) = delete;
	CameraViewport& operator=(CameraViewport&&) = delete;
	virtual ~CameraViewport();

	void setImage(nfx::VideoFrame&);

private:
	nfx::GUI::VerticalLayout m_mainLayout;

	nfx::GUI::Image* m_image;
};
