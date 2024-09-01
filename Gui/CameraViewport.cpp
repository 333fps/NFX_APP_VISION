#include "pch/pch.h"
#include "CameraViewport.h"

// #include <nfx/VideoCapture/VideoCaptureDeviceInfo.h>
// #include <nfx/VideoCapture/VideoResolution.h>

#include <nfx/Graphics/GL/Objects/Texture2D.h>
#include <nfx/Graphics/GL/Functions/Functions_4_5.h>

#include <GL/glcorearb.h>
#include <GL/gl.h>

#include <imgui.h>
#include <implot.h>

CameraViewport::CameraViewport()
{
}

CameraViewport::~CameraViewport()
{
}

void CameraViewport::draw()
{
	if (ImGui::Begin("cam0"))
	{
		ImGui::Text("pointer = %p", imageTexture_cam0);
		ImGui::Text("size = %d x %d", 800, 600);
		ImGui::Image((void*)(intptr_t)imageTexture_cam0, ImVec2(800, 600));
		ImGui::End();
	}
}

void CameraViewport::setFrame(const cv::Mat& frame)
{
	(void)frame;
	std::cout << "received" << std::endl;

	BindCVMat2GLTexture(frame);
}

void CameraViewport::BindCVMat2GLTexture(const cv::Mat& frame)
{
	nfx::Graphics::GL::Functions_4_5 f;
	// f.initializeOpenGLFunctions();

	static bool first{ true };
	if (first)
	{
		initTexture(frame);
	}

	f.glBindTexture(GL_TEXTURE_2D, imageTexture_cam0); // Allocate GPU memory for handle (Texture ID)

	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set texture clamping method
	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);

	f.glTexImage2D(GL_TEXTURE_2D, // Type of texture
		0,						  // Pyramid level (for mip-mapping) - 0 is the top level
		GL_RGB,					  // Internal colour format to convert to
		frame.cols,				  // Image width  i.e. 640 for Kinect in standard mode
		frame.rows,				  // Image height i.e. 480 for Kinect in standard mode
		0,						  // Border width in pixels (can either be 1 or 0)
		GL_RGB,					  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
		GL_UNSIGNED_BYTE,		  // Image data type
		frame.ptr()				  // The actual image data itself
	);

	std::cout << frame.cols << "," << frame.rows << std::endl;
}

void CameraViewport::initTexture(const cv::Mat& frame)
{
	nfx::Graphics::GL::Functions_4_5 f;

	f.glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	f.glGenTextures(1, &imageTexture_cam0);			   // Gen a new texture and store the handle
	f.glBindTexture(GL_TEXTURE_2D, imageTexture_cam0); // Allocate GPU memory for handle (Texture ID)

	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set texture clamping method
	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	f.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}