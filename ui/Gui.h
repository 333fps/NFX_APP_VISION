#pragma once

#include <nfx/GUI/MainWidget.h>

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

class GUI : public nfx::GUI::MainWidget
{
public:
	explicit GUI(nfx::Window::Window* p_window, nfx::Window::Context* p_context);
	GUI() = delete;
	GUI(const GUI&) = delete;
	GUI& operator=(const GUI&) = delete;
	GUI(GUI&&) = delete;
	GUI& operator=(GUI&&) = delete;
	virtual ~GUI();

	void update();

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
