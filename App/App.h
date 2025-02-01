#pragma once

#include <nfx/Application/Application.h>

namespace nfx
{
	namespace Window
	{
		class Window;
		class Context;
	}

	namespace Graphics
	{
		namespace GL
		{
			class Renderer;
		}
	}
}

// using namespace nfx;

class MainWidget;
class App final : public nfx::Application
{
public:
	App(const std::string& p_name, const std::string& p_version,
		short p_width, short p_height);
	App() = delete;
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	App(App&&) = delete;
	App& operator=(App&&) = delete;
	virtual ~App();

	virtual int run(int argc, char* argv[]) override;

private:
	virtual bool init() override;

	void update();
	void render();
	void processEvents();

private:
	std::unique_ptr<nfx::Window::Window> m_window;
	std::unique_ptr<nfx::Window::Context> m_context;
	std::unique_ptr<MainWidget> m_gui;

	std::unique_ptr<nfx::Graphics::GL::Renderer> m_renderer;
};
