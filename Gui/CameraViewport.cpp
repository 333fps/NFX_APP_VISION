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
	// nfx::Graphics::GL::Functions_4_5 f;
	// f.initializeOpenGLFunctions();

	// p_frameBuffer->release();
}

CameraViewport::~CameraViewport()
{
}

void CameraViewport::draw()
{
	if (!ok)
	{
		return;
	}

	if (!m_frame.empty() && !oktowrite.load())
	{
		// nfx::Graphics::GL::Functions_4_5 f;
		// f.initializeOpenGLFunctions();

		static bool first{ true };

		if (first)
		{
			m_texture = new nfx::Graphics::GL::Texture2D{
				nullptr,
				(short)m_frame.cols, (short)m_frame.rows,
				nfx::Graphics::GL::TextureFormat::BGR,
				nfx::Graphics::GL::TextureUnit::Unit0,
				nfx::Graphics::GL::TextureType::Diffuse,
				nfx::Graphics::GL::TextureMinFilter::Nearest,
				nfx::Graphics::GL::TextureMagFilter::Nearest,
				nfx::Graphics::GL::TextureWrapMode::ClampToBorder,
				nfx::Graphics::GL::TextureWrapMode::ClampToBorder
			};

			first = false;
		}

		// m_texture->bind();

		m_texture->update((char*)m_frame.ptr());

		// m_texture->release();

		oktowrite.store(true);
	}

	if (!m_texture)
	{
		return;
	}

	if (ImGui::Begin("cam0"))
	{
		ImGui::Image((void*)(intptr_t)m_texture->id(), ImVec2(m_frame.cols, m_frame.rows));
	}
	ImGui::End();
}

void CameraViewport::setFrame(const cv::Mat& frame)
{
	if (oktowrite)
	{
		m_frame = frame;
		oktowrite.store(false);
		ok = true;
	}
}
