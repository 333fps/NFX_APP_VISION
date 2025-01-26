#pragma once

#include <nfx/Application/Application.h>

namespace nfx
{
	namespace Window2
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

class GUI;
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
	std::unique_ptr<nfx::Window2::Window> m_window;
	std::unique_ptr<nfx::Window2::Context> m_context;
	std::unique_ptr<GUI> m_gui;

	std::unique_ptr<nfx::Graphics::GL::Renderer> m_renderer;
};
