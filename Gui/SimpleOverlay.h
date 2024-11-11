#pragma once

#include <nfx/GUI/Widget.h>
#include <nfx/GUI/VerticalLayout.h>
#include <nfx/GUI/Label.h>

namespace nfx::Window
{
	class Window;
}

class SimpleOverlay final : public nfx::GUI::Widget
{
public:
	SimpleOverlay(nfx::Window::Window* p_window);
	SimpleOverlay() = delete;
	SimpleOverlay(const SimpleOverlay&) = delete;
	SimpleOverlay& operator=(const SimpleOverlay&) = delete;
	SimpleOverlay(SimpleOverlay&&) = delete;
	SimpleOverlay& operator=(SimpleOverlay&&) = delete;
	virtual ~SimpleOverlay();

	virtual void update() override;
	virtual void draw() override;

private:
	nfx::Window::Window* m_window = nullptr;

	const char* m_hardwareInfo = nullptr;
	const char* m_OpenGlVersion = nullptr;

private:
	nfx::GUI::VerticalLayout m_layout;
	nfx::GUI::Label m_lblHardwareinfo;
	nfx::GUI::Label m_lblHardwareinfoValue;
	nfx::GUI::Label m_lblOpenGLinfo;
	nfx::GUI::Label m_lblOpenGLinfoValue;
	nfx::GUI::Label m_lblFramerate;
	nfx::GUI::Label m_lblMousePosition;
};
