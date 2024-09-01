#include "pch/pch.h"
#include "App/App.h"

int main(int argc, char* argv[])
{
	App app{ "NFX_APP_VISION", "1.0", 1920, 1080 };

	return app.run(argc, argv);
}