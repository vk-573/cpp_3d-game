#include <iostream>
#include "GameApplication.hpp"

int main() {
	GameApplication app;
	srand(time(NULL));

	app.init(1600, 900);
	app.start();
	return 0;
}