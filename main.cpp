#include "App/App.h"

int main(int argc, char* argv[])
{
	App app{ "NFX_APP_VISION", "1.0", 1280, 720 };
	auto b = app.run(argc, argv);

	return b;
}