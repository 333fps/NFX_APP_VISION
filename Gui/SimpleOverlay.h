#pragma once

namespace nfx::Window
{
	class Window;
}

class SimpleOverlay final
{
public:
	SimpleOverlay(nfx::Window::Window* p_window);
	SimpleOverlay() = delete;
	SimpleOverlay(const SimpleOverlay&) = delete;
	SimpleOverlay& operator=(const SimpleOverlay&) = delete;
	SimpleOverlay(SimpleOverlay&&) = delete;
	SimpleOverlay& operator=(SimpleOverlay&&) = delete;
	~SimpleOverlay();

	void draw() const;

private:
	nfx::Window::Window* m_window = nullptr;

	const char* m_hardwareInfo = nullptr;
	const char* m_OpenGlVersion = nullptr;
};
