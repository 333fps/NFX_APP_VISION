#include "CameraController.h"

#include <nfx/VideoCapture/VideoCaptureDeviceInfo.h>
#include <nfx/VideoCapture/VideoCaptureDevice.h>
#include <nfx/VideoCapture/VideoFormat.h>
#include <nfx/VideoCapture/Enums.h>
#include <nfx/VideoCapture/BackEndInfo.h>

#include <spdlog/spdlog.h>

CameraController::CameraController() : nfx::GUI::Window{ "Camera controller" }
{
	{
		m_checkBoxCamera = new nfx::GUI::CheckBox{ "Start/Stop" };
		m_checkBoxFlipH = new nfx::GUI::CheckBox{ "Flip horizontally", true };
		m_checkBoxFlipV = new nfx::GUI::CheckBox{ "Flip vertically" };

		m_comboCameras = new nfx::GUI::Combo{ "Cameras" };
		m_comboResolutions = new nfx::GUI::Combo{ "res" };
	}

	{
		m_mainLayout.addWidget(m_comboCameras);
		m_mainLayout.addWidget(m_comboResolutions);

		m_mainLayout.addWidget(m_checkBoxCamera);

		m_mainLayout.addLayout(&m_hLayout);

		m_brightnessSlider = new nfx::GUI::Slider{ "Brightness" };

		m_hLayout.addWidget(m_checkBoxFlipV);
		m_hLayout.addWidget(m_checkBoxFlipH);

		{
			m_contrastSlider = new nfx::GUI::Slider{ "Contrast" };
			m_hueSlider = new nfx::GUI::Slider{ "Hue" };
			m_saturationSlider = new nfx::GUI::Slider{ "Saturation" };
			m_sharpnessSlider = new nfx::GUI::Slider{ "Sharpness" };
			m_gammaSlider = new nfx::GUI::Slider{ "Gamma" };
			m_whiteBalanceSlider = new nfx::GUI::Slider{ "White balance" };
			m_backLightCompensationSlider = new nfx::GUI::Slider{ "Backlight compensation" };
			m_gainSlider = new nfx::GUI::Slider{ "Gain" };

			m_panSlider = new nfx::GUI::Slider{ "Pan" };
			m_tiltSlider = new nfx::GUI::Slider{ "Tilt" };
			m_rollSlider = new nfx::GUI::Slider{ "Roll" };
			m_zoomSlider = new nfx::GUI::Slider{ "Zoom" };
			m_exposureSlider = new nfx::GUI::Slider{ "Exposure" };
			m_irisSlider = new nfx::GUI::Slider{ "Iris" };
			m_focusSlider = new nfx::GUI::Slider{ "Focus" };

			m_lblCaptureBackend = new nfx::GUI::Label{ "Capture backend: " + nfx::backendName() };
			m_lblCaptureBackend->setEnable(false);

			m_lblCameraVendor = new nfx::GUI::Label{ "Camera vendor: " };
			m_lblCameraVendor->setEnable(false);

			m_lblCameraFPS = new nfx::GUI::Label{ "Camera fps: " };
			m_lblCameraFPS->setText(fmt::format("Camera fps {:.3f}", 0.f));
			m_lblCameraFPS->setEnable(false);

			m_mainLayout.addWidget(m_brightnessSlider);
			m_mainLayout.addWidget(m_contrastSlider);
			m_mainLayout.addWidget(m_hueSlider);
			m_mainLayout.addWidget(m_saturationSlider);
			m_mainLayout.addWidget(m_sharpnessSlider);
			m_mainLayout.addWidget(m_gammaSlider);
			m_mainLayout.addWidget(m_whiteBalanceSlider);
			m_mainLayout.addWidget(m_backLightCompensationSlider);
			m_mainLayout.addWidget(m_gainSlider);

			m_mainLayout.addWidget(m_panSlider);
			m_mainLayout.addWidget(m_tiltSlider);
			m_mainLayout.addWidget(m_rollSlider);
			m_mainLayout.addWidget(m_zoomSlider);
			m_mainLayout.addWidget(m_exposureSlider);
			m_mainLayout.addWidget(m_irisSlider);
			m_mainLayout.addWidget(m_focusSlider);

			m_mainLayout.addWidget(m_lblCaptureBackend);
			m_mainLayout.addWidget(m_lblCameraVendor);
			m_mainLayout.addWidget(m_lblCameraFPS);

			m_brightnessSlider->setEnable(false);
			m_contrastSlider->setEnable(false);
			m_hueSlider->setEnable(false);
			m_saturationSlider->setEnable(false);
			m_sharpnessSlider->setEnable(false);
			m_gammaSlider->setEnable(false);
			m_whiteBalanceSlider->setEnable(false);
			m_backLightCompensationSlider->setEnable(false);
			m_gainSlider->setEnable(false);

			m_panSlider->setEnable(false);
			m_tiltSlider->setEnable(false);
			m_rollSlider->setEnable(false);
			m_zoomSlider->setEnable(false);
			m_exposureSlider->setEnable(false);
			m_irisSlider->setEnable(false);
			m_focusSlider->setEnable(false);
		}

		setLayout(&m_mainLayout);
	}

	{
		auto videoDeviceInfoList = nfx::VideoCaptureDeviceInfo::availableVideoDevices();
		videoDeviceInfoList.sort();

		unsigned i{ 0 };
		for (const auto& device : videoDeviceInfoList)
		{
			m_comboCameras->addItem(device.name());

			m_comboCameras->setData(i, std::pair(device.vendor(), device.formats()));

			++i;
		}
	}

	{ // Callbacks
		m_comboCameras->registerIndexChangeCallback(std::bind(&CameraController::cameraIndexChanged, this, std::placeholders::_1));

		m_checkBoxCamera->registerStateChangeCallback(std::bind(&CameraController::cameraCheckBoxClicked, this, std::placeholders::_1));

		m_brightnessSlider->registerValueChangeCallback(std::bind(&CameraController::brightnessSliderValueChanged, this, std::placeholders::_1));
		m_contrastSlider->registerValueChangeCallback(std::bind(&CameraController::contrastSliderValueChanged, this, std::placeholders::_1));
		m_hueSlider->registerValueChangeCallback(std::bind(&CameraController::hueSliderValueChanged, this, std::placeholders::_1));
		m_saturationSlider->registerValueChangeCallback(std::bind(&CameraController::saturationSliderValueChanged, this, std::placeholders::_1));
		m_sharpnessSlider->registerValueChangeCallback(std::bind(&CameraController::sharpnessSliderValueChanged, this, std::placeholders::_1));
		m_gammaSlider->registerValueChangeCallback(std::bind(&CameraController::gammaSliderValueChanged, this, std::placeholders::_1));
		m_whiteBalanceSlider->registerValueChangeCallback(std::bind(&CameraController::whiteBalanceSliderValueChanged, this, std::placeholders::_1));
		m_backLightCompensationSlider->registerValueChangeCallback(std::bind(&CameraController::backLightCompensationSliderValueChanged, this, std::placeholders::_1));
		m_gainSlider->registerValueChangeCallback(std::bind(&CameraController::gainSliderValueChanged, this, std::placeholders::_1));

		m_panSlider->registerValueChangeCallback(std::bind(&CameraController::panSliderValueChanged, this, std::placeholders::_1));
		m_tiltSlider->registerValueChangeCallback(std::bind(&CameraController::tiltSliderValueChanged, this, std::placeholders::_1));
		m_rollSlider->registerValueChangeCallback(std::bind(&CameraController::rollSliderValueChanged, this, std::placeholders::_1));
		m_zoomSlider->registerValueChangeCallback(std::bind(&CameraController::zoomSliderValueChanged, this, std::placeholders::_1));
		m_exposureSlider->registerValueChangeCallback(std::bind(&CameraController::exposureSliderValueChanged, this, std::placeholders::_1));
		m_irisSlider->registerValueChangeCallback(std::bind(&CameraController::irisSliderValueChanged, this, std::placeholders::_1));
		m_focusSlider->registerValueChangeCallback(std::bind(&CameraController::focusSliderValueChanged, this, std::placeholders::_1));

		m_checkBoxFlipH->registerStateChangeCallback(std::bind(&CameraController::checkBoxFlipHClicked, this, std::placeholders::_1));
		m_checkBoxFlipV->registerStateChangeCallback(std::bind(&CameraController::checkBoxFlipVClicked, this, std::placeholders::_1));
	}
}

CameraController::~CameraController()
{
}

void CameraController::registerFrameReadyCallback(const std::function<void(nfx::Graphics::Image&)>& p_frameReadyCallback)
{
	m_frameReadyCallbacks.push_back(p_frameReadyCallback);
}

void CameraController::cameraIndexChanged(unsigned idx)
{
	m_comboResolutions->clear();

	const auto& data = std::any_cast<std::pair<std::string, std::vector<nfx::VideoFormat>>>(m_comboCameras->data(idx));
	const auto& vendor = data.first;
	const auto& formats = data.second;

	for (const auto& fmt : formats)
	{
		std::stringstream ss;
		ss << fmt.fourcc << " " << fmt.width << "x" << fmt.height << "/" << fmt.bitcount << "bpp @" << fmt.fps << "fps ";
		m_comboResolutions->addItem(ss.str());
	}

	m_lblCameraVendor->setText("Camera vendor: " + vendor);
	m_comboResolutions->setCurrentIndex(m_comboResolutions->count() - 1);
}

void CameraController::cameraCheckBoxClicked(bool b)
{
	if (b)
	{
		m_videoCaptureDevice.reset(new nfx::VideoCaptureDevice{ (uint16_t)m_comboCameras->currentIndex() });

		const auto& data = std::any_cast<std::pair<std::string, std::vector<nfx::VideoFormat>>>(m_comboCameras->currentData());
		const auto& fmt = data.second.at(m_comboResolutions->currentIndex());

		m_videoCaptureDevice->open(fmt.fourcc, fmt.width, fmt.height);

		if (!m_videoCaptureDevice->isOpen())
		{
			SPDLOG_ERROR("Failed to open Capture device \"{}\".", m_comboCameras->currentText());
			return;
		}

		m_videoCaptureDevice->registerFrameReadyCallback(
			std::bind(
				&CameraController::onFrameReady,
				this,
				std::placeholders::_1));

		SPDLOG_INFO("Capture device \"{}\" opened successfully.", m_comboCameras->currentText());
		{
			m_comboCameras->setEnable(false);
			m_comboResolutions->setEnable(false);
		}

		if (m_checkBoxFlipH->isChecked())
		{
			m_videoCaptureDevice->flipHorizontally(true);
		}
		if (m_checkBoxFlipV->isChecked())
		{
			m_videoCaptureDevice->flipVertically(true);
		}

		updateSettings();
		updateControls();

		{ // TODO
			m_videoCaptureDevice->setAutoExposure(true);
			m_videoCaptureDevice->setAutoWhiteBalance(false);
		}
	}
	else
	{
		if (m_videoCaptureDevice && m_videoCaptureDevice->isOpen())
		{
			SPDLOG_INFO("Closing capture device \"{}\".", m_comboCameras->currentText());
			m_videoCaptureDevice->close();

			if (!m_videoCaptureDevice->isOpen())
			{
				SPDLOG_INFO("Capture device \"{}\" closed.", m_comboCameras->currentText());

				m_lblCameraFPS->setText(fmt::format("Camera fps {:.3f}", 0.f));

				m_comboCameras->setEnable(true);
				m_comboResolutions->setEnable(true);

				{
					m_brightnessSlider->setValue(0);
					m_contrastSlider->setValue(0);
					m_hueSlider->setValue(0);
					m_saturationSlider->setValue(0);
					m_sharpnessSlider->setValue(0);
					m_gammaSlider->setValue(0);
					m_whiteBalanceSlider->setValue(0);
					m_backLightCompensationSlider->setValue(0);
					m_gainSlider->setValue(0);

					m_brightnessSlider->setRange(0, 0, 0, 0);
					m_contrastSlider->setRange(0, 0, 0, 0);
					m_hueSlider->setRange(0, 0, 0, 0);
					m_saturationSlider->setRange(0, 0, 0, 0);
					m_sharpnessSlider->setRange(0, 0, 0, 0);
					m_gammaSlider->setRange(0, 0, 0, 0);
					m_whiteBalanceSlider->setRange(0, 0, 0, 0);
					m_backLightCompensationSlider->setRange(0, 0, 0, 0);
					m_gainSlider->setRange(0, 0, 0, 0);

					m_brightnessSlider->setEnable(false);
					m_contrastSlider->setEnable(false);
					m_hueSlider->setEnable(false);
					m_saturationSlider->setEnable(false);
					m_sharpnessSlider->setEnable(false);
					m_gammaSlider->setEnable(false);
					m_whiteBalanceSlider->setEnable(false);
					m_backLightCompensationSlider->setEnable(false);
					m_gainSlider->setEnable(false);
				}

				{
					m_panSlider->setValue(0);
					m_tiltSlider->setValue(0);
					m_rollSlider->setValue(0);
					m_zoomSlider->setValue(0);
					m_exposureSlider->setValue(0);
					m_irisSlider->setValue(0);
					m_focusSlider->setValue(0);

					m_panSlider->setRange(0, 0, 0, 0);
					m_tiltSlider->setRange(0, 0, 0, 0);
					m_rollSlider->setRange(0, 0, 0, 0);
					m_zoomSlider->setRange(0, 0, 0, 0);
					m_exposureSlider->setRange(0, 0, 0, 0);
					m_irisSlider->setRange(0, 0, 0, 0);
					m_focusSlider->setRange(0, 0, 0, 0);

					m_panSlider->setEnable(false);
					m_tiltSlider->setEnable(false);
					m_rollSlider->setEnable(false);
					m_zoomSlider->setEnable(false);
					m_exposureSlider->setEnable(false);
					m_irisSlider->setEnable(false);
					m_focusSlider->setEnable(false);
				}
			}
			else
			{
				SPDLOG_ERROR("Failed to close Capture device \"{}\".", m_comboCameras->currentText());
			}

			m_videoCaptureDevice.release();
		}
		else
		{
			SPDLOG_WARN("Capture device is not open or already closed.");
		}
	}
}

void CameraController::brightnessSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Brightness, m_brightnessSlider->getCurrentValue());
	}
}

void CameraController::contrastSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Contrast, m_contrastSlider->getCurrentValue());
	}
}

void CameraController::hueSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Hue, m_hueSlider->getCurrentValue());
	}
}

void CameraController::saturationSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Saturation, m_saturationSlider->getCurrentValue());
	}
}

void CameraController::sharpnessSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Sharpness, m_sharpnessSlider->getCurrentValue());
	}
}

void CameraController::gammaSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Gamma, m_gammaSlider->getCurrentValue());
	}
}

void CameraController::whiteBalanceSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::WhiteBalance, m_whiteBalanceSlider->getCurrentValue());
	}
}

void CameraController::backLightCompensationSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::BacklightCompensation, m_backLightCompensationSlider->getCurrentValue());
	}
}

void CameraController::gainSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureCapability::Gain, m_gainSlider->getCurrentValue());
	}
}

void CameraController::panSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Pan, m_panSlider->getCurrentValue());
	}
}

void CameraController::tiltSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Tilt, m_tiltSlider->getCurrentValue());
	}
}

void CameraController::rollSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Roll, m_rollSlider->getCurrentValue());
	}
}

void CameraController::zoomSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Zoom, m_zoomSlider->getCurrentValue());
	}
}

void CameraController::exposureSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Exposure, m_exposureSlider->getCurrentValue());
	}
}

void CameraController::irisSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Iris, m_irisSlider->getCurrentValue());
	}
}

void CameraController::focusSliderValueChanged(float)
{
	if (m_videoCaptureDevice)
	{
		m_videoCaptureDevice->setCurrentValue(nfx::VideoCaptureControl::Focus, m_focusSlider->getCurrentValue());
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

	{ // Brightness
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Brightness);

		if (range.max != 0)
		{
			m_brightnessSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_brightnessSlider->setValue(range.dflt);
			m_brightnessSlider->setEnable(true);
		}
		else
		{
			m_brightnessSlider->setEnable(false);
		}
	}

	{ // Contrast
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Contrast);

		if (range.max != 0)
		{
			m_contrastSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_contrastSlider->setValue(range.dflt);
			m_contrastSlider->setEnable(true);
		}
		else
		{
			m_contrastSlider->setEnable(false);
		}
	}

	{ // Hue
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Hue);

		if (range.max != 0)
		{
			m_hueSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_hueSlider->setValue(range.dflt);
			m_hueSlider->setEnable(true);
		}
		else
		{
			m_hueSlider->setEnable(false);
		}
	}

	{ // Saturation
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Saturation);

		if (range.max != 0)
		{
			m_saturationSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_saturationSlider->setValue(range.dflt);
			m_saturationSlider->setEnable(true);
		}
		else
		{
			m_saturationSlider->setEnable(false);
		}
	}

	{ // Sharpness
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Sharpness);

		if (range.max != 0)
		{
			m_sharpnessSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_sharpnessSlider->setValue(range.dflt);
			m_sharpnessSlider->setEnable(true);
		}
		else
		{
			m_sharpnessSlider->setEnable(false);
		}
	}

	{ // Gamma
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Gamma);

		if (range.max != 0)
		{
			m_gammaSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_gammaSlider->setValue(range.dflt);
			m_gammaSlider->setEnable(true);
		}
		else
		{
			m_gammaSlider->setEnable(false);
		}
	}

	{ // WhiteBalance
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::WhiteBalance);

		if (range.max != 0)
		{
			m_whiteBalanceSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_whiteBalanceSlider->setValue(range.dflt);
			m_whiteBalanceSlider->setEnable(true);
		}
		else
		{
			m_whiteBalanceSlider->setEnable(false);
		}
	}

	{ // BacklightCompensation
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::BacklightCompensation);

		if (range.max != 0)
		{
			m_backLightCompensationSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_backLightCompensationSlider->setValue(range.dflt);
			m_backLightCompensationSlider->setEnable(true);
		}
		else
		{
			m_backLightCompensationSlider->setEnable(false);
		}
	}

	{ // Gain
		range = m_videoCaptureDevice->range(nfx::VideoCaptureCapability::Gain);

		if (range.max != 0)
		{
			m_gainSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_gainSlider->setValue(range.dflt);
			m_gainSlider->setEnable(true);
		}
		else
		{
			m_gainSlider->setEnable(false);
		}
	}
}

void CameraController::updateControls()
{
	nfx::VideoCaptureControlRange range{};

	{ // Pan
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Pan);

		if (range.max != 0)
		{
			m_panSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_panSlider->setValue(range.dflt);
			m_panSlider->setEnable(true);
		}
		else
		{
			m_panSlider->setEnable(false);
		}
	}

	{ // Tilt
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Tilt);

		if (range.max != 0)
		{
			m_tiltSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_tiltSlider->setValue(range.dflt);
			m_tiltSlider->setEnable(true);
		}
		else
		{
			m_tiltSlider->setEnable(false);
		}
	}

	{ // Roll
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Roll);

		if (range.max != 0)
		{
			m_rollSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_rollSlider->setValue(range.dflt);
			m_rollSlider->setEnable(true);
		}
		else
		{
			m_rollSlider->setEnable(false);
		}
	}

	{ // Zoom
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Zoom);

		if (range.max != 0)
		{
			m_zoomSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_zoomSlider->setValue(range.dflt);
			m_zoomSlider->setEnable(true);
		}
		else
		{
			m_zoomSlider->setEnable(false);
		}
	}

	{ // Exposure
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Exposure);

		if (range.max != 0)
		{
			m_exposureSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_exposureSlider->setValue(range.dflt);
			m_exposureSlider->setEnable(true);
		}
		else
		{
			m_exposureSlider->setEnable(false);
		}
	}

	{ // Iris
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Iris);

		if (range.max != 0)
		{
			m_irisSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_irisSlider->setValue(range.dflt);
			m_irisSlider->setEnable(true);
		}
		else
		{
			m_irisSlider->setEnable(false);
		}
	}

	{ // Focus
		range = m_videoCaptureDevice->range(nfx::VideoCaptureControl::Focus);

		if (range.max != 0)
		{
			m_focusSlider->setRange(range.min, range.max, range.step, range.dflt);
			m_focusSlider->setValue(range.dflt);
			m_focusSlider->setEnable(true);
		}
		else
		{
			m_focusSlider->setEnable(false);
		}
	}
}

void CameraController::onFrameReady(nfx::Graphics::Image& frame)
{
	if (m_videoCaptureDevice)
	{
		m_lblCameraFPS->setText(fmt::format("Camera fps {:.3f}", m_videoCaptureDevice->fps()).c_str());
	}

	for (const auto& cb : m_frameReadyCallbacks)
	{
		cb(frame);
	}
}
