#pragma once

#include <nfx/Window2/Window.h>
#include <nfx/GUI/MenuBar.h>
#include <nfx/GUI/Menu.h>
#include <nfx/GUI/MenuItem.h>

class MenuBar final : public nfx::GUI::MenuBar
{
public:
	MenuBar(nfx::Window2::Window* p_window);
	MenuBar(const MenuBar&) = delete;
	MenuBar& operator=(const MenuBar&) = delete;
	MenuBar(MenuBar&&) = delete;
	MenuBar& operator=(MenuBar&&) = delete;
	virtual ~MenuBar();

private:
	nfx::Window2::Window* m_window;

	nfx::GUI::Menu* m_fileMenu;
	nfx::GUI::MenuItem* m_menuItem;
	nfx::GUI::MenuItem* m_menuItemQuit;
	nfx::GUI::MenuItem* m_menuItemFullscreen;

private:
	void quitCallBack(int id, const char* label, const char* internalName);
};
