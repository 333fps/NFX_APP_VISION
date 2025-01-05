#pragma once

#include <nfx/GUI/Panel.h>
#include <nfx/GUI/VerticalLayout.h>
#include <nfx/GUI/HorizontalLayout.h>
#include <nfx/GUI/Combo.h>
#include <nfx/GUI/CheckBox.h>
#include <nfx/GUI/Slider.h>
#include <nfx/GUI/Label.h>

#include <nfx/VideoCapture/VideoCaptureDevice.h>

class CameraController final : public nfx::GUI::Panel
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
	nfx::GUI::Combo* m_comboResolutions;

	nfx::GUI::CheckBox* m_checkBoxCamera;
	nfx::GUI::CheckBox* m_checkBoxFlipH;
	nfx::GUI::CheckBox* m_checkBoxFlipV;

	nfx::GUI::Slider* m_brightnessSlider;
	nfx::GUI::Slider* m_contrastSlider;
	nfx::GUI::Slider* m_hueSlider;
	nfx::GUI::Slider* m_saturationSlider;
	nfx::GUI::Slider* m_sharpnessSlider;
	nfx::GUI::Slider* m_gammaSlider;
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

public:
	void registerFrameReadyCallback(std::function<void(nfx::Graphics::Image)> p_frameReadyCallback);
	void update();

private:
	std::unique_ptr<nfx::VideoCaptureDevice> m_videoCaptureDevice;
	std::vector<std::function<void(nfx::Graphics::Image)>> m_frameReadyCallbacks;

	void onFrameReady(nfx::Graphics::Image fr);

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

	void frameReadyCallback(nfx::Graphics::Image frame);
};
