#include "Gui.h"

#include <nfx/Window/Window.h>

#include <nfx/Graphics/Core/Camera3D.h>

#include "SimpleOverlay.h"
#include "CameraController.h"
#include "CameraViewport.h"

GUI::GUI(nfx::Window::Window* p_window) : nfx::GUI::GUI{ p_window },
										  m_window{ p_window },
										  m_simpleOverlay{ new SimpleOverlay{ p_window } },
										  m_cameraViewport{ new CameraViewport{} },
										  m_cameraController{ new CameraController{ m_cameraViewport } }
{
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

void GUI::draw(nfx::Graphics::Camera3D* p_cam)
{
	(void)p_cam;

	beginFrame();

	m_simpleOverlay->draw();
	m_cameraController->draw();
	m_cameraViewport->draw();

	endFrame();
}