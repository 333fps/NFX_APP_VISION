#pragma once

#include <algorithm>

namespace nfx
{
	struct VideoFrame
	{
		int width;
		int height;
		int channels;
		void* pixels;
		int stride;
	};
}
