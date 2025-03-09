#include "App/App.h"

#include <spdlog/spdlog.h>

int main(int argc, char* argv[])
{
	spdlog::set_level(spdlog::level::debug);

	App app{ "NFX_APP_VISION", "1.0", 1920, 1080 };

	return app.run(argc, argv);
}
