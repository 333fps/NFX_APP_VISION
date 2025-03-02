#pragma once

#include <nfx/GUI.h>


class StatusBar final : public nfx::GUI::StatusBar
{
public:
	StatusBar();
	StatusBar(const StatusBar&) = delete;
	StatusBar& operator=(const StatusBar&) = delete;
	StatusBar(StatusBar&&) = delete;
	StatusBar& operator=(StatusBar&&) = delete;
	virtual ~StatusBar();

	void setFrameRate(float p_frameRate);
	void setFrameTime(float p_frameRate);

private:
	nfx::GUI::Label* m_lblFramerate;
	nfx::GUI::Label* m_lblFrameTime;
	nfx::GUI::Label* m_lblHardwareInfo;
	nfx::GUI::Label* m_lblOpenGlVersion;
};
