#include "StatusBar.h"

#include <nfx/Graphics/GL/Functions/Functions_1_0.h>
#include <GL/glcorearb.h>

#include <spdlog/spdlog.h>

StatusBar::StatusBar() : nfx::GUI::StatusBar{}
{
	m_lblFramerate = new nfx::GUI::Label{};
	m_lblFrameTime = new nfx::GUI::Label{};

	nfx::Graphics::GL::Functions_1_0 f;
	m_lblHardwareInfo = new nfx::GUI::Label{ std::string("GPU: ") + std::string(reinterpret_cast<const char*>(f.glGetString(GL_RENDERER))) };
	m_lblOpenGlVersion = new nfx::GUI::Label{ std::string("GL Version: ") + std::string(reinterpret_cast<const char*>(f.glGetString(GL_VERSION))) };

	addWidget(m_lblFramerate);
	addSeparator();
	addWidget(m_lblFrameTime);
	addSeparator();
	addWidget(m_lblHardwareInfo);
	addSeparator();
	addWidget(m_lblOpenGlVersion);

	setVisible(true);
}

StatusBar::~StatusBar()
{
}

void StatusBar::setFrameRate(float p_frameRate)
{
	m_lblFramerate->setText(fmt::format("Framerate: {:.2f} FPS", p_frameRate));
}

void StatusBar::setFrameTime(float p_frameRate)
{
	m_lblFrameTime->setText(fmt::format("Frametime: {:.4f} ms", p_frameRate));
}
