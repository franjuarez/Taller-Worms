
#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include "client.h"
#include "../game_src/game.h"

#include <iostream>

int main(int argc, char** argv) {
	if (argc < 3) 
		return 1;

	try {
		Client client(argv[1], argv[2]);
		client.connect();
	} catch (const std::exception& e) {
		return 1;
	}
	return 0;
}
