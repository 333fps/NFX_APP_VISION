#include "VideoCaptureDevice.h"

#include "nfx/Image/Image.h"

#include <nfx/Utils/ElapsedTime.h>

#include <spdlog/spdlog.h>

VideoCaptureDevice::VideoCaptureDevice(uint16_t p_hardwareIndex) : m_hardwareIndex{ p_hardwareIndex }
{
}

VideoCaptureDevice::~VideoCaptureDevice()
{
	if (isOpen())
	{
		close();
	}
}

bool VideoCaptureDevice::open(uint16_t p_width, uint16_t p_height, uint16_t p_fps)
{
	std::cout << cv::getBuildInformation() << "\n";

#ifdef _WIN32
	auto api = cv::CAP_DSHOW;
	// auto api = cv::CAP_ANY;
#elif defined __linux
	auto api = cv::CAP_V4L2;
#endif

	bool ret{ false };
	try
	{
		ret = m_videoCapture.open(
			m_hardwareIndex,
			api,
			std::vector<int>{
				cv::CAP_PROP_FRAME_WIDTH, p_width,
				cv::CAP_PROP_FRAME_HEIGHT, p_height,
				cv::CAP_PROP_FPS, p_fps });
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL TO OPEN" << e.what() << "\n";
	}

	jt = std::jthread(std::bind_front(&VideoCaptureDevice::aquireFrame, this));
	// jt.detach();
	int fourcc = static_cast<int>(m_videoCapture.get(cv::CAP_PROP_FOURCC));

	m_fourCC = {
		(char)(fourcc & 0XFF), (char)((fourcc & 0XFF00) >> 8), (char)((fourcc & 0XFF0000) >> 16), (char)((fourcc & 0XFF000000) >> 24), 0
	};
	std::cout << "FOURCC is '" << m_fourCC << "'\n";

	return ret;
}

bool VideoCaptureDevice::open(const nfx::VideoResolution& p_VideoResolution)
{
	return open(p_VideoResolution.x, p_VideoResolution.y, p_VideoResolution.fps);
}

void VideoCaptureDevice::close()
{
	jt.request_stop();
}

bool VideoCaptureDevice::isOpen() const
{
	return m_videoCapture.isOpened();
}

float VideoCaptureDevice::fps() const
{
	return m_fps;
}

void VideoCaptureDevice::registerFrameReadyCallback(std::function<void(cv::Mat)> p_frameReadyCallback)
{
	m_frameReadyCallbacks.push_back(p_frameReadyCallback);
}

void VideoCaptureDevice::onFrameReady()
{
	for (const auto& cb : m_frameReadyCallbacks)
	{
		auto frame = m_frame.clone();
		cb(frame);
	}

	m_frame = cv::Mat{};
}

void VideoCaptureDevice::aquireFrame(std::stop_token token)
{
	while (!token.stop_requested())
	{
		static auto previousTime = nfx::Utils::ElapsedTime::asMilliSeconds<double>();

		try
		{
			if (m_videoCapture.read(m_frame))
			{
				if (!m_frame.empty())
				{
					onFrameReady();
				}
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << "\n";
		}

		auto timeNow = nfx::Utils::ElapsedTime::asMilliSeconds<double>();
		m_fps = (float)(timeNow - previousTime);
		previousTime = timeNow;
	}

	m_videoCapture.release();

	SPDLOG_WARN("stopping");
	// cv::destroyAllWindows();
}