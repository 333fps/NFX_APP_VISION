#include "SimpleOverlay.h"

#include <nfx/Window/Window.h>
#include <nfx/Window/Inputs.h>

#include <nfx/Graphics/GL/Functions/Functions_1_0.h>
#include <GL/glcorearb.h>

#include <spdlog/spdlog.h>

SimpleOverlay::SimpleOverlay(nfx::Window::Window* p_window) : nfx::GUI::GroupBox{ "Debug infos" },
															  m_window{ p_window }
{
	nfx::Graphics::GL::Functions_1_0 f;
	m_hardwareInfo = reinterpret_cast<const char*>(f.glGetString(GL_RENDERER));
	m_OpenGlVersion = reinterpret_cast<const char*>(f.glGetString(GL_VERSION));

	m_lblHardwareinfo.setText("Hardware info:");
	m_lblHardwareinfoValue.setText(m_hardwareInfo);

	m_lblOpenGLinfo.setText("OpenGL version:");
	m_lblOpenGLinfoValue.setText(m_OpenGlVersion);

	m_Vlayout = new nfx::GUI::VerticalLayout;
	setLayout(m_Vlayout);

	m_Vlayout->addWidget(&m_lblHardwareinfo);
	m_Vlayout->addWidget(&m_lblHardwareinfoValue);

	m_Vlayout->addWidget(&m_lblOpenGLinfo);
	m_Vlayout->addWidget(&m_lblOpenGLinfoValue);

	m_Vlayout->addWidget(&m_lblFramerate);
	m_Vlayout->addWidget(&m_lblMousePosition);
}

SimpleOverlay::~SimpleOverlay()
{
}

void SimpleOverlay::update()
{
	m_lblFramerate.setText(std::format("Framerate {:.2f}FPS / Frametime {:.4f}ms", 1. / m_window->deltaTime(), m_window->deltaTime()));

	auto mousePos = m_window->mousePosition();
	if (mousePos.valid)
	{
		m_lblMousePosition.setText(std::format("Mouse Position: ({:.1f},{:.1f})", (double)m_window->mousePosition().x, (double)m_window->mousePosition().y));
	}
	else
	{
		m_lblMousePosition.setText("Mouse Position: <invalid>");
	}
}

void SimpleOverlay::draw()
{
	nfx::GUI::GroupBox::draw();
	// m_Vlayout->draw();
}