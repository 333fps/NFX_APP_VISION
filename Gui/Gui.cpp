#include "Gui.h"

#include <nfx/Window/Window.h>

#include <nfx/Graphics/Core/Camera3D.h>

#include "SimpleOverlay.h"
#include "CameraController.h"
#include "CameraViewport.h"

GUI::GUI(nfx::Window::Window* p_window) : nfx::GUI::MainWidget{ p_window },
										  m_simpleOverlay{ new SimpleOverlay{ p_window } },
										  m_cameraViewport{ new CameraViewport{} },
										  m_cameraController{ new CameraController{ m_cameraViewport } }
{
	auto centralWidget = this->centralWidget();

	m_gridLayout.setPaddingX(10);
	m_gridLayout.setPaddingY(10);

	m_gridLayout.addWidget(m_cameraController, 0, 0);
	m_gridLayout.addWidget(m_cameraViewport, 0, 1);
	m_gridLayout.addWidget(m_simpleOverlay, 1, 0);

	centralWidget->setLayout(&m_gridLayout);
}

GUI ::~GUI()
{
	delete m_simpleOverlay;
	delete m_cameraController;
	delete m_cameraViewport;
}

void GUI::update()
{
	m_simpleOverlay->update();
	m_cameraController->update();
	m_cameraViewport->update();
}
