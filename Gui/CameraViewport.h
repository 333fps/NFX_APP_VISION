#pragma once

#include <nfx/GUI/Widget.h>

#include <nfx/GUI/Image.h>

#include <nfx/GUI/VerticalLayout.h>

#include <nfx/Graphics/Core/Image.h>
#include <nfx/Graphics/GL/Definitions.h>

namespace nfx
{
	namespace Graphics
	{
		namespace GL
		{
			class Texture2D;
		}
	}
}

class CameraViewport final : public nfx::GUI::Widget
{
public:
	CameraViewport();
	CameraViewport(const CameraViewport&) = delete;
	CameraViewport& operator=(const CameraViewport&) = delete;
	CameraViewport(CameraViewport&&) = delete;
	CameraViewport& operator=(CameraViewport&&) = delete;
	virtual ~CameraViewport();

	virtual void update() override;
	virtual void draw() override;

public:
	void setFrame(nfx::Graphics::Image frame);

private:
	nfx::Graphics::GL::Texture2D* m_texture;

	nfx::Graphics::Image m_frame;

	std::atomic<bool> m_waitingForFrame{ true };

	nfx::GUI::VerticalLayout m_mainLayout;
	nfx::GUI::Image* m_image;
};
