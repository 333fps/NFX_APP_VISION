#pragma once

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
	void setFrame(nfx::Graphics::Image frame);

private:
	GLuint imageTexture_cam0;

	nfx::Graphics::GL::Texture2D* m_texture;

	nfx::Graphics::Image m_frame;

	std::atomic<bool> m_waitingForFrame{ true };
};
