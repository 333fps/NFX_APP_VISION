#include "MenuBar.h"

#include <spdlog/spdlog.h>

MenuBar::MenuBar(nfx::Window::Window* p_window) : nfx::GUI::MenuBar{},
												  m_window{ p_window }
{
	m_fileMenu = new nfx::GUI::Menu{ "File", true };

	m_menuItem = new nfx::GUI::MenuItem{ "item1", "shortcut1", true };
	m_menuItemQuit = new nfx::GUI::MenuItem{ "Quit", "Ctrl+Q", true };
	m_menuItemFullscreen = new nfx::GUI::MenuItem{ "Fullscreen", "F8", true };

	m_fileMenu->addMenuItem(m_menuItem);
	m_fileMenu->addSeparator();
	m_fileMenu->addMenuItem(m_menuItemFullscreen);
	m_fileMenu->addSeparator();
	m_fileMenu->addMenuItem(m_menuItemQuit);

	addMenu(m_fileMenu);

	m_menuItemFullscreen->registerClickCallback(std::bind(&nfx::Window::Window::toggleFullscreen, p_window));
	m_menuItemQuit->registerClickCallback(std::bind(&MenuBar::quitCallBack, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	setVisible(true);
}

MenuBar::~MenuBar()
{
}

void MenuBar::quitCallBack([[maybe_unused]] int id, [[maybe_unused]] const char* label, [[maybe_unused]] const char* internalName)
{
	m_window->requestClose();
}
