#pragma once

#include <nfx/GUI/GUI.h>

namespace nfx
{
	namespace Window
	{
		class Window;
	}
	namespace Graphics
	{
		class Camera3D;
	}
}

class SimpleOverlay;
class CameraController;
class CameraViewport;

class GUI : public nfx::GUI::GUI
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
	void draw(nfx::Graphics::Camera3D* p_cam = nullptr);

	nfx::Window::Window* m_window = nullptr;

private:
	SimpleOverlay* m_simpleOverlay = nullptr;
	CameraViewport* m_cameraViewport = nullptr;
	CameraController* m_cameraController = nullptr;
};
