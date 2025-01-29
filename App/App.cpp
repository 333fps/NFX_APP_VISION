#include "App.h"

#include <nfx/Window/Api.h>
#include <nfx/Window/Window.h>
#include <nfx/Window/Context.h>
// #include <nfx/Window/OpenGLHints.h>
#include <nfx/Graphics/GL/Enums.h>
#include <nfx/Graphics/GL/Scene/Renderer.h>
#include <nfx/Graphics/GL/Utils/Debugger.h>
#include <nfx/Graphics/Core/Color.h>

#include <nfx/Graphics/GL/Functions/Functions_4_5.h>

#include "ui/Gui.h"

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

	if (!init())
	{
		SPDLOG_ERROR("Failed to initialize the application.");
		return EXIT_FAILURE;
	}

	SPDLOG_INFO("Starting {}, v{}", m_name, m_version);

	while (!m_window->shouldClose())
	{
		update();

		render();

		processEvents();
	}

	m_gui->teardown();

	// m_context->tearDown();

	return EXIT_SUCCESS;
}

void App::update()
{
	m_gui->updateGUI();
	m_gui->update();
}

void App::render()
{
	m_context->beginFrame();

	{
		m_renderer->begin();
		m_renderer->setViewport(0, 0, m_window->width(), m_window->height());

		m_gui->drawGUI();
	}

	m_context->endFrame();
}

void App::processEvents()
{
	m_window->pollEvents();
}

bool App::init()
{
	m_window = std::make_unique<nfx::Window::Window>(nfx::Window::Api::OpenGL, m_width, m_height, m_name);

	m_context = std::make_unique<nfx::Window::Context>(nfx::Window::Api::OpenGL);

	m_context->beginFrame();

	m_renderer = std::make_unique<nfx::Graphics::GL::Renderer>();

	{
		// m_context->enableVSync(true);
		//  m_window->enableNativeCursor(false);
		m_window->show();
	}

	{
		m_renderer->setClearColor(nfx::Graphics::Color{ 125, 143, 110, 255 });
		m_renderer->enableClearBuffer(nfx::Graphics::GL::RenderBuffer::Color, true);
		m_renderer->enableClearBuffer(nfx::Graphics::GL::RenderBuffer::Depth, true);
		m_renderer->enableClearBuffer(nfx::Graphics::GL::RenderBuffer::Stencil, false);
	}

	nfx::Graphics::GL::Functions_4_5 f;
	f.initializeOpenGLFunctions();

	{
		std::vector<unsigned int> ignore{};
		nfx::Graphics::GL::Debugger::init(ignore);
		nfx::Graphics::GL::Debugger::breakOnError(false);
		nfx::Graphics::GL::Debugger::breakOnWarning(false);
		nfx::Graphics::GL::Debugger::setSeverityLevel(nfx::Graphics::GL::DebuggerSeverity::Notification);
	}

	m_gui = std::make_unique<GUI>(m_window.get(), m_context.get());

	return true;
}