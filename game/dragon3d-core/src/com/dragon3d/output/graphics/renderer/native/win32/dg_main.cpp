#include <stdlib.h>

#include "dg_game.h"
#include "dg_engine.h"
#include "dg_win_platform.h"
#include "dg_opengl_v15_lib.h"
#include "dg_application.h"

//#pragma warning (disable: C4996)
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main(int argc, char *argv[]){
	DGPlatform* platform = new DGWinPlatform();
	DGEngine* engine = new DGEngine();
	DGApplication* app = new DGApplication();

	if (engine->init(platform, "Dragon Game Windows", 480, 725)) {
		app->startup(engine);
		engine->run();
		app->end(engine);
	}

	dgDelete(app);
	dgDelete(engine);
	dgDelete(platform);
}