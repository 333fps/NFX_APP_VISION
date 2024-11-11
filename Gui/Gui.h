#pragma once

// #include <nfx/GUI/GUI.h>

#include <nfx/GUI/MainWidget.h>
#include <nfx/GUI/GridLayout.h>

namespace nfx
{
	namespace Window
	{
		class Window;
	}
}

class SimpleOverlay;
class CameraController;
class CameraViewport;

class GUI : public nfx::GUI::MainWidget
{
public:
	explicit GUI(nfx::Window::Window* p_window);
	GUI() = delete;
	GUI(const GUI&) = delete;
	GUI& operator=(const GUI&) = delete;
	GUI(GUI&&) = delete;
	GUI& operator=(GUI&&) = delete;
	virtual ~GUI();

	void update();

private:
	nfx::GUI::GridLayout m_gridLayout{ 2, 2 };

	SimpleOverlay* m_simpleOverlay = nullptr;
	CameraViewport* m_cameraViewport = nullptr;
	CameraController* m_cameraController = nullptr;
};
