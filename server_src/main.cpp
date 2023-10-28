
#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include "../shared_src/socket.h"
#include "lobby.h"

#include <iostream>
#include <string>
#include <utility>
#include <arpa/inet.h>

int main(int argc, char** argv) {

	if (argc < 2) {
		throw std::runtime_error("Invalid arguments");
		return 1;
	}

	Socket skt(argv[1]);
	Lobby lobby(skt);

	return 0;
}
