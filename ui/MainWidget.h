#pragma once

#include <nfx/GUI/MainWindow.h>

#include "MenuBar.h"
#include "StatusBar.h"
#include "CameraController.h"
#include "CameraViewport.h"

namespace nfx
{
	namespace Window
	{
		class Window;
		class Context;

		namespace Inputs
		{
			struct KeyState;
		}
	}
}

class MainWidget : public nfx::GUI::MainWindow
{
public:
	explicit MainWidget(nfx::Window::Window* p_window, nfx::Window::Context* p_context);
	MainWidget() = delete;
	MainWidget(const MainWidget&) = delete;
	MainWidget& operator=(const MainWidget&) = delete;
	MainWidget(MainWidget&&) = delete;
	MainWidget& operator=(MainWidget&&) = delete;
	virtual ~MainWidget();

private:
	nfx::Window::Window* m_window;

private:
	MenuBar* m_menuBar;
	StatusBar m_statusBar;

	CameraController* m_cameraController;
	CameraViewport* m_cameraViewport;

	nfx::GUI::DockSpace* m_dockSpace;

private:
	void updateCallback();
	void keyCallback(nfx::Window::Inputs::KeyState p_keyState);
};
