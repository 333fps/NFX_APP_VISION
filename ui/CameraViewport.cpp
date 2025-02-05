#include "CameraViewport.h"

#include <spdlog/spdlog.h>

CameraViewport::CameraViewport() : nfx::GUI::Window{ "Camera viewport", 320, 240 }
{
	setLayout(&m_mainLayout);

	m_image = new nfx::GUI::Image;

	m_mainLayout.addWidget(m_image);
}

CameraViewport::~CameraViewport()
{
	delete m_image;
}

void CameraViewport::setImage(nfx::Graphics::Image& img)
{
	m_image->setImage(img);
}
