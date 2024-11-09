#include "App.h"

#include <nfx/Window/Window.h>
#include <nfx/Window/Context.h>
#include <nfx/Window/OpenGLHints.h>
#include <nfx/Graphics/GL/Enums.h>
#include <nfx/Graphics/GL/Scene/Renderer.h>
#include <nfx/Graphics/GL/Objects/FrameBuffer.h>
#include <nfx/Graphics/GL/Utils/Debugger.h>
#include <nfx/Graphics/Core/Color.h>

#include <nfx/Graphics/GL/Functions/Functions_4_5.h>

#include "Gui/Gui.h"

#include <spdlog/spdlog.h>

App::App(const std::string& p_name, const std::string& p_version, short p_width, short p_height)
	: nfx::Application{ p_name, p_version, p_width, p_height }
{
}

App::~App()
{
}

int App::run(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	init();

	SPDLOG_INFO("Starting {:s}, v{:s}", m_name, m_version);

	m_window->enableVSync(true);
	m_window->enableNativeCursor(false);
	m_window->show();

	m_renderer->setClearColor(nfx::Graphics::Color{ 125, 143, 110, 255 });
	m_renderer->enableClearBuffer(nfx::Graphics::GL::RenderBuffer::Color, true);
	m_renderer->enableClearBuffer(nfx::Graphics::GL::RenderBuffer::Depth, true);
	m_renderer->enableClearBuffer(nfx::Graphics::GL::RenderBuffer::Stencil, false);

	{
		std::vector<unsigned int> ignore{};
		nfx::Graphics::GL::Debugger::init(ignore);
		nfx::Graphics::GL::Debugger::breakOnError(true);
		nfx::Graphics::GL::Debugger::breakOnWarning(false);
		nfx::Graphics::GL::Debugger::setSeverityLevel(nfx::Graphics::GL::DebuggerSeverity::Notification);
	}

	while (!m_window->shouldClose())
	{
		processEvents();

		update();

		render();
	}

	m_context->tearDown();

	return EXIT_SUCCESS;
}

void App::update()
{
	m_gui->update();
}

void App::render()
{
	m_context->beginFrame(m_window.get());

	{
		m_renderer->begin();
		m_renderer->setViewport(0, 0, m_window->width(), m_window->height());

		m_gui->draw();
	}

	m_context->endFrame(m_window.get());
}

void App::processEvents()
{
	m_window->pollEvents();
}

bool App::init()
{
	nfx::Window::OpenGLHints::setVersion(nfx::Window::OpenGLHints::Version::OpengGL_4_5_core);
	m_window = std::make_unique<nfx::Window::Window>(nfx::Window::Api::OpenGL, m_width, m_height, m_name.c_str());
	if (!m_window->isValid())
	{
		return EXIT_FAILURE;
	}

	m_context = std::make_unique<nfx::Window::Context>(nfx::Window::Api::OpenGL, m_window.get());
	if (!m_context->isValid())
	{
		return EXIT_FAILURE;
	}

	m_renderer = std::make_unique<nfx::Graphics::GL::Renderer>();

	m_gui = std::make_unique<::GUI>(m_window.get());

	nfx::Graphics::GL::Functions_4_5 f;
	f.initializeOpenGLFunctions();

	return EXIT_SUCCESS;
}