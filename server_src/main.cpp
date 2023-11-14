
#include "../shared_src/socket.h"
#include "lobby.h"
#include "game_loop.h"

#include <iostream>
#include <string>
#include <utility>
#include <arpa/inet.h>

int main(int argc, char** argv) {

	if (argc < 2) {
		throw std::runtime_error("Invalid arguments");
		return 1;
	}


	const std::string hostname(argv[1]);
	Lobby lobby(hostname, 1, "");

	lobby.run();
	
	return 0;
}

