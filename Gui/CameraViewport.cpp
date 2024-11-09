#include "CameraViewport.h"

// #include <nfx/VideoCapture/VideoCaptureDeviceInfo.h>
// #include <nfx/VideoCapture/VideoResolution.h>

#include <nfx/Graphics/GL/Objects/Texture2D.h>
#include <nfx/Graphics/GL/Functions/Functions_4_5.h>

#include <GL/glcorearb.h>
#include <GL/gl.h>

#include <imgui.h>
#include <implot.h>

#include <spdlog/spdlog.h>

#include <glm/glm.hpp>

CameraViewport::CameraViewport()
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
}

CameraViewport::~CameraViewport()
{
	delete m_texture;
}

void CameraViewport::draw()
{
	if (m_texture->width() != (unsigned)m_frame.width || m_texture->height() != (unsigned)m_frame.height)
	{
		m_texture->resize((short)m_frame.width, (short)m_frame.height);
	}

	if (!m_waitingForFrame.load())
	{
		m_texture->update((void*)m_frame.pixels.data());

		m_waitingForFrame.store(true);
	}

	ImGuiWindowFlags window_flags = 0;

	if (ImGui::Begin("cam0", nullptr, window_flags))
	{
		auto viewportSize = ImGui::GetContentRegionAvail();
		float imageAspectRatio = (float)m_frame.width / (float)m_frame.height;
		float contentRegionAspectRatio = viewportSize.x / viewportSize.y;

		if (contentRegionAspectRatio > imageAspectRatio)
		{
			float imageWidth = viewportSize.y * imageAspectRatio;
			float xPadding = (viewportSize.x - imageWidth) / 2;
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xPadding);
			ImGui::Image((ImTextureID)(intptr_t)m_texture->id(), ImVec2(imageWidth, viewportSize.y));
		}
		else
		{
			float imageHeight = viewportSize.x / imageAspectRatio;
			float yPadding = (viewportSize.y - imageHeight) / 2;
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + yPadding);
			ImGui::Image((ImTextureID)(intptr_t)m_texture->id(), ImVec2(viewportSize.x, imageHeight));
		}
	}

	ImGui::End();
}

void CameraViewport::setFrame(nfx::Graphics::Image frame)
{
	if (m_waitingForFrame.load())
	{
		m_frame = frame;
		m_waitingForFrame.store(false);
	}
}
