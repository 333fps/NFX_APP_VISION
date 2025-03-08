#pragma once

#include <nfx/Graphics.h>

#include <nfx/GUI.h>

#include <nfx/VideoCapture.h>

class CameraController final : public nfx::GUI::Window
{
public:
	CameraController();
	CameraController(const CameraController&) = delete;
	CameraController& operator=(const CameraController&) = delete;
	CameraController(CameraController&&) = delete;
	CameraController& operator=(CameraController&&) = delete;
	virtual ~CameraController();

private:
	nfx::GUI::VerticalLayout m_mainLayout;
	nfx::GUI::HorizontalLayout m_hLayout;

	nfx::GUI::Combo* m_comboCameras;
	nfx::GUI::Combo* m_comboFormats;

	nfx::GUI::CheckBox* m_checkBoxCamera;
	nfx::GUI::CheckBox* m_checkBoxFlipH;
	nfx::GUI::CheckBox* m_checkBoxFlipV;

	nfx::GUI::Slider* m_brightnessSlider;
	nfx::GUI::Slider* m_contrastSlider;
	nfx::GUI::Slider* m_hueSlider;
	nfx::GUI::Slider* m_saturationSlider;
	nfx::GUI::Slider* m_sharpnessSlider;
	nfx::GUI::Slider* m_gammaSlider;
	nfx::GUI::Slider* m_colorSlider;
	nfx::GUI::Slider* m_whiteBalanceSlider;
	nfx::GUI::Slider* m_backLightCompensationSlider;
	nfx::GUI::Slider* m_gainSlider;

	nfx::GUI::Slider* m_panSlider;
	nfx::GUI::Slider* m_tiltSlider;
	nfx::GUI::Slider* m_rollSlider;
	nfx::GUI::Slider* m_zoomSlider;
	nfx::GUI::Slider* m_exposureSlider;
	nfx::GUI::Slider* m_irisSlider;
	nfx::GUI::Slider* m_focusSlider;

	nfx::GUI::Label* m_lblCaptureBackend;
	nfx::GUI::Label* m_lblCameraFPS;
	nfx::GUI::Label* m_lblCameraVendor;

public:
	void registerFrameReadyCallback(const std::function<void(nfx::VideoFrame&)>& p_frameReadyCallback);

private:
	std::unique_ptr<nfx::VideoCaptureDevice> m_videoCaptureDevice;
	std::vector<std::function<void(nfx::VideoFrame&)>> m_frameReadyCallbacks;

private:
	// Callbacks
	void cameraIndexChanged(unsigned);
	void cameraCheckBoxClicked(bool);

	void brightnessSliderValueChanged(float);
	void contrastSliderValueChanged(float);
	void hueSliderValueChanged(float);
	void saturationSliderValueChanged(float);
	void sharpnessSliderValueChanged(float);
	void gammaSliderValueChanged(float);
	void colorSliderValueChanged(float);
	void whiteBalanceSliderValueChanged(float);
	void backLightCompensationSliderValueChanged(float);
	void gainSliderValueChanged(float);

	void panSliderValueChanged(float);
	void tiltSliderValueChanged(float);
	void rollSliderValueChanged(float);
	void zoomSliderValueChanged(float);
	void exposureSliderValueChanged(float);
	void irisSliderValueChanged(float);
	void focusSliderValueChanged(float);

	void checkBoxFlipVClicked(bool);
	void checkBoxFlipHClicked(bool);
	void updateSettings();
	void updateControls();

	// void onFrameReady(nfx::Graphics::Image& frame);
	void onFrameReady(nfx::VideoFrame& frame);
};
