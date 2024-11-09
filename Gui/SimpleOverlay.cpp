#include "SimpleOverlay.h"

#include <nfx/Window/Window.h>
#include <nfx/Window/Inputs.h>

#include <nfx/Graphics/GL/Functions/Functions_1_0.h>
#include <GL/glcorearb.h>

SimpleOverlay::SimpleOverlay(nfx::Window::Window* p_window) : Widget{ "Simple overlay" },
															  m_window{ p_window }
{
	nfx::Graphics::GL::Functions_1_0 f;
	m_hardwareInfo = reinterpret_cast<const char*>(f.glGetString(GL_RENDERER));
	m_OpenGlVersion = reinterpret_cast<const char*>(f.glGetString(GL_VERSION));

	setLayout(&m_layout);

	m_lblHardwareinfo.setText("Hardware info:");
	m_lblHardwareinfoValue.setText(m_hardwareInfo);

	m_lblOpenGLinfo.setText("OpenGL version:");
	m_lblOpenGLinfoValue.setText(m_OpenGlVersion);

	m_layout.addWidget(&m_lblHardwareinfo);
	m_layout.addWidget(&m_lblHardwareinfoValue);

	m_layout.addWidget(&m_lblOpenGLinfo);
	m_layout.addWidget(&m_lblOpenGLinfoValue);

	m_layout.addWidget(&m_lblFramerate);
	m_layout.addWidget(&m_lblMousePosition);
}

SimpleOverlay::~SimpleOverlay()
{
}

void SimpleOverlay::draw()
{
	m_lblFramerate.setText(std::format("Framerate {:.2f}FPS / Frametime {:.4f}ms", 1. / m_window->deltaTime(), m_window->deltaTime()).c_str());

	auto mousePos = m_window->mousePosition();
	if (mousePos.valid)
	{
		m_lblMousePosition.setText(std::format("Mouse Position: ({:.1f},{:.1f})", (double)m_window->mousePosition().x, (double)m_window->mousePosition().y).c_str());
	}
	else
	{
		m_lblMousePosition.setText("Mouse Position: <invalid>");
	}

	drawLayout();
}