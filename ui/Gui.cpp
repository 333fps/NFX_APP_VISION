#include "Gui.h"

#include <nfx/Window/Window.h>
#include <nfx/Window/Context.h>
#include "nfx/Window/Inputs.h"
#include <nfx/GUI/DockSpace.h>

#include <spdlog/spdlog.h>

GUI::GUI(nfx::Window::Window* p_window, nfx::Window::Context* p_context)
	: nfx::GUI::MainWidget{ p_window, p_context },
	  m_window{ p_window }
{
	{
		m_menuBar = new MenuBar{ p_window };
		setMenuBar(m_menuBar);
		setStatusBar(&m_statusBar);
	}

	{
		m_dockSpace = new nfx::GUI::DockSpace{};
		setDockSpace(m_dockSpace);
	}

	{
		m_cameraController = new CameraController{};
		m_cameraViewport = new CameraViewport{};
	}

	{
		addPanel(m_cameraController);
		addPanel(m_cameraViewport);
	}

	registerUpdateCallbackFunc(std::bind(&GUI::updateCallback, this));
	// p_window->registerKeyCallback(std::bind(&GUI::keyCallback, this, std::placeholders::_1));

	m_cameraController->registerFrameReadyCallback(
		std::bind(
			&CameraViewport::setImage,
			m_cameraViewport,
			std::placeholders::_1));
}

GUI::~GUI()
{
	SPDLOG_INFO("GUI destroyed.");
}

void GUI::update()
{
	m_cameraController->update();

	m_statusBar.setFrameRate(2.f);

	// auto a = frameRate();

	// SPDLOG_INFO(a);
}

void GUI::updateCallback()
{
	m_statusBar.setFrameRate(frameRate());
	m_statusBar.setFrameTime(deltaTime());
}

void GUI::keyCallback(nfx::Window::Inputs::KeyState p_keyState)
{
	if (p_keyState.key == nfx::Window::Inputs::Key::KeyF8 && p_keyState.state == nfx::Window::Inputs::State::Up)
	{
		SPDLOG_INFO("F8 key pressed.");
		m_window->toggleFullscreen();
	}
}
