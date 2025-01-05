#include "CameraViewport.h"

#include <spdlog/spdlog.h>

CameraViewport::CameraViewport() : nfx::GUI::Panel{ "Camera viewport" }
{
	setLayout(&m_mainLayout);

	m_image = new nfx::GUI::Image;

	m_mainLayout.addWidget(m_image);
}

CameraViewport::~CameraViewport()
{
	delete m_image;
}

void CameraViewport::setImage(nfx::Graphics::Image img)
{
	// SPDLOG_ERROR("{} {}", img.width, img.height);

	m_image->setImage(img);
}
