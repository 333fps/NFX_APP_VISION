#pragma once

#include <nfx/GUI/Panel.h>
#include <nfx/GUI/VerticalLayout.h>

#include <nfx/GUI/Image.h>

class CameraViewport final : public nfx::GUI::Panel
{
public:
	CameraViewport();
	CameraViewport(const CameraViewport&) = delete;
	CameraViewport& operator=(const CameraViewport&) = delete;
	CameraViewport(CameraViewport&&) = delete;
	CameraViewport& operator=(CameraViewport&&) = delete;
	virtual ~CameraViewport();

	void setImage(nfx::Graphics::Image&);

private:
	nfx::GUI::VerticalLayout m_mainLayout;

	nfx::GUI::Image* m_image;
};
