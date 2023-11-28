
#include "../shared_src/socket.h"
#include "lobby.h"
#include "game_loop.h"

#include <iostream>
#include <string>
#include <utility>
#include <arpa/inet.h>

#define HARDCODED_PLAYERS 1

int main(int argc, char** argv) {

	if (argc < 2) {
		throw std::runtime_error("Invalid arguments");
		return 1;
	}


	const std::string hostname(argv[1]);
	bool playing = true;
	Lobby lobby(hostname, HARDCODED_PLAYERS, "subsuelo de fiuba", &playing);

	lobby.start();

	while (std::cin.get() != 'q') {}

	std::cout << "Closing server..." << std::endl;

	playing = false;
	lobby.stop();
	std::cout << "Waiting for lobby to close..." << std::endl;
	lobby.join();
	std::cout << "Server closed" << std::endl;
	
	return 0;
}

