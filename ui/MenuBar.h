#pragma once

#include <nfx/Window/Window.h>
#include <nfx/GUI/MenuBar.h>
#include <nfx/GUI/Menu.h>
#include <nfx/GUI/MenuItem.h>

class MenuBar final : public nfx::GUI::MenuBar
{
public:
	MenuBar(nfx::Window::Window* p_window);
	MenuBar(const MenuBar&) = delete;
	MenuBar& operator=(const MenuBar&) = delete;
	MenuBar(MenuBar&&) = delete;
	MenuBar& operator=(MenuBar&&) = delete;
	virtual ~MenuBar();

private:
	nfx::Window::Window* m_window;

	nfx::GUI::Menu* m_fileMenu;
	nfx::GUI::MenuItem* m_menuItemQuit;
	nfx::GUI::MenuItem* m_menuItemFullscreen;

private:
	void quitCallBack(int id, const char* label, const char* internalName);
};
