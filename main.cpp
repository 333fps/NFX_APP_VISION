#include "App/App.h"

int main(int argc, char* argv[])
{
	App app{ "NFX_APP_VISION", "1.0", 1280, 720 };

	return app.run(argc, argv);
}
