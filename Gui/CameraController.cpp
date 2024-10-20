#include "CameraController.h"

#include <nfx/VideoCapture/VideoCaptureDeviceInfo.h>
#include <nfx/VideoCapture/VideoCaptureDevice.h>
#include <nfx/VideoCapture/VideoResolution.h>
#include <nfx/VideoCapture/Enums.h>

#include <imgui.h>
#include <implot.h>

#include <spdlog/spdlog.h>

CameraController::CameraController(CameraViewport* p_cameraViewport) : m_cameraViewport{ p_cameraViewport }
{
	{ // Combos
		auto videoDeviceInfoList = nfx::VideoCaptureDeviceInfo::availableVideoDevices();
		videoDeviceInfoList.sort();

		unsigned i{ 0 };
		for (const auto& device : videoDeviceInfoList)
		{
			m_comboCameras.addItem(device.name());

			m_comboCameras.setData(i, device.resolutions());

			++i;
		}
	}

	{ // Checkboxes
		m_checkBoxCamera.setLabel("Start/Stop");
		m_checkBoxFlipH.setLabel("Flip horizontally");
		m_checkBoxFlipH.setChecked(true);
		m_checkBoxFlipV.setLabel("Flip vertically");
	}

	{ // Sliders
		m_brightnessSlider.setLabel("Brightness");
		m_contrastSlider.setLabel("Contrast");
		m_hueSlider.setLabel("Hue");
		m_saturationSlider.setLabel("Saturation");
		m_sharpnessSlider.setLabel("Sharpness");
		m_gammaSlider.setLabel("Gamma");
		m_whiteBalanceSlider.setLabel("White balance");
		m_backLightCompensationSlider.setLabel("Backlight compensation");
		m_gainSlider.setLabel("Gain");

		m_panSlider.setLabel("Pan");
		m_tiltSlider.setLabel("Tilt");
		m_rollSlider.setLabel("Roll");
		m_zoomSlider.setLabel("Zoom");
		m_exposureSlider.setLabel("Exposure");
		m_irisSlider.setLabel("Iris");
		m_focusSlider.setLabel("Focus");
	}

	{ // Callbacks
		m_comboCameras.registerIndexChangeCallback(std::bind(&CameraController::cameraIndexChanged, this, std::placeholders::_1));

		m_checkBoxCamera.registerStateChangeCallback(std::bind(&CameraController::cameraCheckBoxClicked, this, std::placeholders::_1));

		m_brightnessSlider.registerValueChangeCallback(std::bind(&CameraController::brightnessSliderValueChanged, this, std::placeholders::_1));
		m_contrastSlider.registerValueChangeCallback(std::bind(&CameraController::contrastSliderValueChanged, this, std::placeholders::_1));
		m_hueSlider.registerValueChangeCallback(std::bind(&CameraController::hueSliderValueChanged, this, std::placeholders::_1));
		m_saturationSlider.registerValueChangeCallback(std::bind(&CameraController::saturationSliderValueChanged, this, std::placeholders::_1));
		m_sharpnessSlider.registerValueChangeCallback(std::bind(&CameraController::sharpnessSliderValueChanged, this, std::placeholders::_1));
		m_gammaSlider.registerValueChangeCallback(std::bind(&CameraController::gammaSliderValueChanged, this, std::placeholders::_1));
		m_whiteBalanceSlider.registerValueChangeCallback(std::bind(&CameraController::whiteBalanceSliderValueChanged, this, std::placeholders::_1));
		m_backLightCompensationSlider.registerValueChangeCallback(std::bind(&CameraController::backLightCompensationSliderValueChanged, this, std::placeholders::_1));
		m_gainSlider.registerValueChangeCallback(std::bind(&CameraController::gainSliderValueChanged, this, std::placeholders::_1));

		m_panSlider.registerValueChangeCallback(std::bind(&CameraController::panSliderValueChanged, this, std::placeholders::_1));
		m_tiltSlider.registerValueChangeCallback(std::bind(&CameraController::tiltSliderValueChanged, this, std::placeholders::_1));
		m_rollSlider.registerValueChangeCallback(std::bind(&CameraController::rollSliderValueChanged, this, std::placeholders::_1));
		m_zoomSlider.registerValueChangeCallback(std::bind(&CameraController::zoomSliderValueChanged, this, std::placeholders::_1));
		m_exposureSlider.registerValueChangeCallback(std::bind(&CameraController::exposureSliderValueChanged, this, std::placeholders::_1));
		m_irisSlider.registerValueChangeCallback(std::bind(&CameraController::irisSliderValueChanged, this, std::placeholders::_1));
		m_focusSlider.registerValueChangeCallback(std::bind(&CameraController::focusSliderValueChanged, this, std::placeholders::_1));

		m_checkBoxFlipH.registerStateChangeCallback(std::bind(&CameraController::checkBoxFlipHClicked, this, std::placeholders::_1));
		m_checkBoxFlipV.registerStateChangeCallback(std::bind(&CameraController::checkBoxFlipVClicked, this, std::placeholders::_1));
	}
}

CameraController::~CameraController()
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->close();
	}
}

void CameraController::draw()
{
	if (ImGui::Begin("Camera controller", nullptr))
	{
		m_comboCameras.draw();
		m_comboResolutions.draw();

		m_checkBoxCamera.draw();
		m_checkBoxFlipH.draw();
		m_checkBoxFlipV.draw();

		m_brightnessSlider.draw();
		m_contrastSlider.draw();
		m_hueSlider.draw();
		m_saturationSlider.draw();
		m_sharpnessSlider.draw();
		m_gammaSlider.draw();
		m_whiteBalanceSlider.draw();
		m_backLightCompensationSlider.draw();
		m_gainSlider.draw();

		m_panSlider.draw();
		m_tiltSlider.draw();
		m_rollSlider.draw();
		m_zoomSlider.draw();
		m_exposureSlider.draw();
		m_irisSlider.draw();
		m_focusSlider.draw();

		if (m_videoCaptureDevice)
		{
			ImGui::Text("CameraFPS %.3f ", m_videoCaptureDevice->fps());
		}
	}
	ImGui::End();
}

void CameraController::cameraIndexChanged(unsigned idx)
{
	m_comboResolutions.clear();

	const auto& data = std::any_cast<const std::vector<nfx::VideoResolution>&>(m_comboCameras.data(idx));
	for (const auto& res : data)
	{
		std::stringstream ss;
		ss << res.x << "x" << res.y << "/" << res.bitcount << "bpp @" << res.fps << "fps ";

		m_comboResolutions.addItem(ss.str());
	}

	m_comboResolutions.setIndex(m_comboResolutions.count() - 1);
}

void CameraController::cameraCheckBoxClicked(bool b)
{
	if (b)
	{
		m_videoCaptureDevice.reset(new nfx::VideoCaptureDevice{ (uint16_t)m_comboCameras.currentIndex() });

		const auto& data = std::any_cast<const std::vector<nfx::VideoResolution>&>(m_comboCameras.data(m_comboCameras.currentIndex()));
		const auto& resolution = data.at(m_comboResolutions.currentIndex());

		m_videoCaptureDevice->open(resolution.x, resolution.y, resolution.fps);

		m_videoCaptureDevice->registerFrameReadyCallback(
			std::bind(
				&CameraViewport::setFrame,
				m_cameraViewport,
				std::placeholders::_1));

		if (!m_videoCaptureDevice->isOpen())
		{
			return;
		}

		if (m_checkBoxFlipH.isChecked())
		{
			m_videoCaptureDevice->flipHorizontally(true);
		}
		if (m_checkBoxFlipV.isChecked())
		{
			m_videoCaptureDevice->flipVertically(true);
		}

		updateSettings();
		updateControls();

		{ // TODO
			m_videoCaptureDevice->setAutoExposure(true);
		}
	}
	else
	{
		m_videoCaptureDevice->close();
	}
}

void CameraController::brightnessSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Brightness, m_brightnessSlider.getCurrentValue());
	}
}

void CameraController::contrastSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Contrast, m_contrastSlider.getCurrentValue());
	}
}

void CameraController::hueSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Hue, m_hueSlider.getCurrentValue());
	}
}

void CameraController::saturationSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Saturation, m_saturationSlider.getCurrentValue());
	}
}

void CameraController::sharpnessSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Sharpness, m_sharpnessSlider.getCurrentValue());
	}
}

void CameraController::gammaSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Gamma, m_gammaSlider.getCurrentValue());
	}
}

void CameraController::whiteBalanceSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::WhiteBalance, m_whiteBalanceSlider.getCurrentValue());
	}
}

void CameraController::backLightCompensationSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::BacklightCompensation, m_backLightCompensationSlider.getCurrentValue());
	}
}

void CameraController::gainSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Gain, m_gainSlider.getCurrentValue());
	}
}

void CameraController::panSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Pan, m_panSlider.getCurrentValue());
	}
}

void CameraController::tiltSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Tilt, m_tiltSlider.getCurrentValue());
	}
}

void CameraController::rollSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Roll, m_rollSlider.getCurrentValue());
	}
}

void CameraController::zoomSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Zoom, m_zoomSlider.getCurrentValue());
	}
}

void CameraController::exposureSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Exposure, m_exposureSlider.getCurrentValue());
	}
}

void CameraController::irisSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Iris, m_irisSlider.getCurrentValue());
	}
}

void CameraController::focusSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Focus, m_focusSlider.getCurrentValue());
	}
}

void CameraController::checkBoxFlipVClicked(bool b)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->flipVertically(b);
	}
}

void CameraController::checkBoxFlipHClicked(bool b)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->flipHorizontally(b);
	}
}

void CameraController::updateSettings()
{
	nfx::VideoCaptureCapabilityRange range{};
	// float currentValue{ 0.f };

	{ // Brightness
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Brightness);
		m_brightnessSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_brightnessSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::Brightness);
		// m_brightnessSlider.setValue(currentValue);
	}

	{ // Contrast
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Contrast);
		m_contrastSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_contrastSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::Contrast);
		// m_contrastSlider.setValue(currentValue);
	}

	{ // Hue
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Hue);
		m_hueSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_hueSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::Hue);
		// m_hueSlider.setValue(currentValue);
	}

	{ // Saturation
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Saturation);
		m_saturationSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_saturationSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::Saturation);
		// m_saturationSlider.setValue(currentValue);
	}

	{ // Sharpness
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Sharpness);
		m_sharpnessSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_sharpnessSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::Sharpness);
		// m_sharpnessSlider.setValue(currentValue);
	}

	{ // Gamma
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Gamma);
		m_gammaSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_gammaSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::Gamma);
		// m_gammaSlider.setValue(currentValue);
	}

	{ // WhiteBalance
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::WhiteBalance);
		m_whiteBalanceSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_whiteBalanceSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::WhiteBalance);
		// m_whiteBalanceSlider.setValue(currentValue);
	}

	{ // BacklightCompensation
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::BacklightCompensation);
		m_backLightCompensationSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_backLightCompensationSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::BacklightCompensation);
		// m_backLightCompensationSlider.setValue(currentValue);
	}

	{ // Gain
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Gain);
		m_gainSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_gainSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureCapability::Gain);
		// m_gainSlider.setValue(currentValue);
	}
}

void CameraController::updateControls()
{
	nfx::VideoCaptureControlRange range{};
	//	float currentValue{ 0.f };

	{ // Pan
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Pan);
		m_panSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_panSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureControl::Pan);
		// m_panSlider.setValue(currentValue);
	}

	{ // Tilt
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Tilt);
		m_tiltSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_tiltSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureControl::Tilt);
		// m_tiltSlider.setValue(currentValue);
	}

	{ // Roll
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Roll);
		m_rollSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_rollSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureControl::Roll);
		// m_rollSlider.setValue(currentValue);
	}

	{ // Zoom
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Zoom);
		m_zoomSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_zoomSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureControl::Zoom);
		// m_zoomSlider.setValue(currentValue);
	}

	{ // Exposure
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Exposure);
		m_exposureSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_exposureSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureControl::Exposure);
		// m_exposureSlider.setValue(currentValue);
	}

	{ // Iris
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Iris);
		m_irisSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_irisSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureControl::Iris);
		// m_irisSlider.setValue(currentValue);
	}

	{ // Focus
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Focus);
		m_focusSlider.setRange(range.min, range.max, range.step, range.dflt);
		m_focusSlider.setValue(range.dflt);

		// currentValue = m_videoCaptureDevice->getCurrentValue(nfx::VideoCaptureControl::Focus);
		// m_focusSlider.setValue(currentValue);
	}
}
