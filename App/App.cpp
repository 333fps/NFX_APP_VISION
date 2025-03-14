#include "App.h"

/* #include <nfx/Window/Api.h>
#include <nfx/Window/Window.h>
#include <nfx/Window/Context.h>
#include <nfx/Window/Inputs.h>
#include <nfx/Graphics/GL/Enums.h>
#include <nfx/Graphics/GL/Scene/Renderer.h>
#include <nfx/Graphics/GL/Utils/Debugger.h>
#include <nfx/Graphics/Core/Color.h>

#include <nfx/Graphics/GL/Functions/Functions_4_5.h> */

#include <nfx/Window.h>
#include <nfx/Graphics.h>
#include <nfx/GUI.h>

#include "ui/MainWidget.h"

#include <spdlog/spdlog.h>

void keyCBfunc(nfx::Window::Window* p_window, nfx::Window::Inputs::KeyState p_keyState);
void charCBfunc(nfx::Window::Window* p_window, unsigned int p_char);

void keyCBfunc(nfx::Window::Window* p_window, nfx::Window::Inputs::KeyState p_keyState)
{
	SPDLOG_INFO("Key: {}, State: {}, {}", static_cast<int>(p_keyState.key), static_cast<int>(p_keyState.state), p_window->title());
}

void charCBfunc(nfx::Window::Window* p_window, unsigned int p_char)
{
	SPDLOG_INFO("Char: {}, {}", p_char, p_window->title());
}

App::App(const std::string& p_name, const std::string& p_version, uint32_t p_width, uint32_t p_height)
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
		if (m_window->keyState(nfx::Window::Inputs::Key::Escape).state == nfx::Window::Inputs::State::Down)
		{
			SPDLOG_WARN("Escape key pressed, closing the application.");

			m_window->requestClose();
		}
		processEvents();

		update();

		render();
	}

	m_gui->teardown();
	m_gui.reset(); // Explicitly destroy GUI first

	// Then destroy window-related resources in correct order
	m_renderer.reset();
	m_context.reset();
	m_window.reset();

	return EXIT_SUCCESS;
}

void App::update()
{
	m_gui->update();
}

void App::render()
{
	m_renderer->prepareFrame();

	m_gui->draw();

	m_renderer->presentFrame();
}

void App::processEvents()
{
	m_window->pollEvents();
}

bool App::init()
{
	nfx::Window::Window::Config config{ .decoration = nfx::Window::Window::Decoration::Standard };

	m_window = std::make_unique<nfx::Window::Window>(nfx::Window::Api::OpenGL, nfx::Window::Size{ m_width, m_height }, m_name, &config);
	// m_window->setKeyCallback(keyCBfunc);
	m_window->setCharCallback(charCBfunc);

	nfx::Window::Context::GLConfig contextConfig;
	contextConfig.shared = nullptr;

	m_context = std::make_unique<nfx::Window::Context>(nfx::Window::Api::OpenGL, m_window.get(), &contextConfig);

	m_renderer = std::make_unique<nfx::Graphics::GL::Renderer>(m_context.get(), m_window.get());

	{
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
		nfx::Graphics::GL::Debugger::breakOnError(true);
		nfx::Graphics::GL::Debugger::breakOnWarning(true);
		nfx::Graphics::GL::Debugger::setSeverityLevel(nfx::Graphics::GL::DebuggerSeverity::Notification);
	}

	// m_renderer->prepareFrame();
	{
		// auto ui = MainWidget(m_window.get(), m_context.get());
	}

	m_gui = std::make_unique<MainWidget>(m_window.get(), m_context.get());

	return true;
}