#include "MainWidget.h"

#include <nfx/Window.h>

#include <nfx/GUI.h>

#include <spdlog/spdlog.h>

MainWidget::MainWidget(nfx::Window::Window* p_window, nfx::Window::Context* p_context)
	: nfx::GUI::MainWindow{ p_window, p_context },
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
		addWindow(m_cameraController);
		addWindow(m_cameraViewport);
	}

	registerUpdateCallbackFunc(std::bind(&MainWidget::updateCallback, this));
	// p_window->registerKeyCallback(std::bind(&GUI::keyCallback, this, std::placeholders::_1));

	m_cameraController->registerFrameReadyCallback(
		std::bind(
			&CameraViewport::setImage,
			m_cameraViewport,
			std::placeholders::_1));
}

MainWidget::~MainWidget()
{
	SPDLOG_INFO("GUI destroyed.");
}

void MainWidget::updateCallback()
{
	m_statusBar.setFrameRate(frameRate());
	m_statusBar.setFrameTime(deltaTime());
}

void MainWidget::keyCallback(nfx::Window::Inputs::KeyState p_keyState)
{
	if (p_keyState.key == nfx::Window::Inputs::Key::KeyF8 && p_keyState.state == nfx::Window::Inputs::State::Up)
	{
		SPDLOG_INFO("F8 key pressed.");
		m_window->toggleFullscreen();
	}
}
