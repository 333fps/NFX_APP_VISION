#include "CameraViewport.h"

#include <nfx/Graphics/GL/Objects/Texture2D.h>
#include <nfx/Graphics/GL/Functions/Functions_4_5.h>

#include <spdlog/spdlog.h>

CameraViewport::CameraViewport() : nfx::GUI::Widget{ "Camera Viewport" }
{
	m_frame.height = 0;
	m_frame.width = 0;

	m_texture = new nfx::Graphics::GL::Texture2D{
		nullptr,
		0, 0,
		nfx::Graphics::GL::TextureFormat::RGB,
		nfx::Graphics::GL::TextureUnit::Unit0,
		nfx::Graphics::GL::TextureType::Diffuse,
		nfx::Graphics::GL::TextureMinFilter::Nearest,
		nfx::Graphics::GL::TextureMagFilter::Nearest,
		nfx::Graphics::GL::TextureWrapMode::ClampToBorder,
		nfx::Graphics::GL::TextureWrapMode::ClampToBorder
	};

	m_image = new nfx::GUI::Image{ m_texture->id(), (short)m_frame.width, (short)m_frame.height };

	m_mainLayout.addWidget(m_image);

	setLayout(&m_mainLayout);
}

CameraViewport::~CameraViewport()
{
	delete m_texture;
	delete m_image;
}

void CameraViewport::draw()
{
	if (m_texture->width() != (unsigned)m_frame.width || m_texture->height() != (unsigned)m_frame.height)
	{
		m_texture->resize((short)m_frame.width, (short)m_frame.height);
		m_image->resize((short)m_frame.width, (short)m_frame.height);
	}

	if (!m_waitingForFrame.load())
	{
		m_texture->update((void*)m_frame.pixels.data());

		m_waitingForFrame.store(true);
	}

	drawLayout();
}

void CameraViewport::setFrame(nfx::Graphics::Image frame)
{
	if (m_waitingForFrame.load())
	{
		m_frame = frame;
		m_waitingForFrame.store(false);
	}
}
