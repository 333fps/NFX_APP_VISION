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
	m_texture = new nfx::Graphics::GL::Texture2D{
		nullptr,
		0, 0,
		nfx::Graphics::GL::TextureFormat::BGR,
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
}

void CameraViewport::draw()
{
	if (m_texture->width() != (unsigned)m_frame.cols || m_texture->height() != (unsigned)m_frame.rows)
	{
		m_texture->resize((short)m_frame.cols, (short)m_frame.rows);
	}

	if (!m_waitingForFrame.load())
	{
		m_texture->update((void*)m_frame.ptr());

		m_waitingForFrame.store(true);
	}

	if (ImGui::Begin("cam0"))
	{
		auto viewportSize = ImGui::GetContentRegionAvail();
		float imageAspectRatio = (float)m_frame.cols / (float)m_frame.rows;
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

void CameraViewport::setFrame(const cv::Mat& frame)
{
	if (m_waitingForFrame.load())
	{
		m_frame = frame;
		m_waitingForFrame.store(false);
	}
}
