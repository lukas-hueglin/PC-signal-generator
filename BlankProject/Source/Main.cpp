#include "Application.h"
#include "Functional.h"

int main(int argc, char** argv) {
	
	// create new application
	App* app = new App(argc, argv);

	return app->exec();
}