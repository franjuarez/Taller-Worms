#include "screen.h"
#include <chrono>
#include <iostream>

int main() {
	Game game;
	Screen screen(game);
	screen.start();
	return 0;
}
