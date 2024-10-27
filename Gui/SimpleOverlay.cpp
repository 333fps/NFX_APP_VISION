#include "SimpleOverlay.h"

#include <nfx/Window/Window.h>
#include <nfx/Window/Inputs.h>

#include <nfx/Graphics/GL/Functions/Functions_1_0.h>
#include <GL/glcorearb.h>

#include <imgui.h>

SimpleOverlay::SimpleOverlay(nfx::Window::Window* p_window) : m_window{ p_window }
{
	nfx::Graphics::GL::Functions_1_0 f;
	m_hardwareInfo = reinterpret_cast<const char*>(f.glGetString(GL_RENDERER));
	m_OpenGlVersion = reinterpret_cast<const char*>(f.glGetString(GL_VERSION));
}

SimpleOverlay::~SimpleOverlay()
{
}

void SimpleOverlay::draw() const
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration		  //
									| ImGuiWindowFlags_AlwaysAutoResize	  //
									| ImGuiWindowFlags_NoFocusOnAppearing //
									| ImGuiWindowFlags_NoNav;

	if (ImGui::Begin("Simple overlay", nullptr, window_flags))
	{
		ImGui::Text("Hardware info:");
		ImGui::TextUnformatted(m_hardwareInfo);
		ImGui::Text("OpenGL Version:");
		ImGui::TextUnformatted(m_OpenGlVersion);

		ImGui::Text("\nFramerate %.2f FPS / Frametime %.4f ms", 1. / m_window->deltaTime(), m_window->deltaTime());

		if (ImGui::IsMousePosValid())
		{
			ImGui::Text("\nMouse Position: (%.1f,%.1f)", (double)m_window->mousePosition().x, (double)m_window->mousePosition().y);
		}
		else
		{
			ImGui::Text("\nMouse Position: <invalid>");
		}
	}
	ImGui::End();
}