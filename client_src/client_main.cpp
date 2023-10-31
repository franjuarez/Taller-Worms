
#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include "client.h"
#include "../game_src/game.h"

#include <iostream>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv) {
	if (argc < 3){
		throw std::runtime_error("Invalid arguments!");
		return ERROR;
	}

	try {
		Client client(argv[1], argv[2]);
		client.start();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return ERROR;
	}
	return SUCCESS;
}
