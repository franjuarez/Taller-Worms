
#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include "client.h"

#include <chrono>
#include <iostream>

int main(int argc, char** argv) {

	if (argc < 3) 
		return 1;

	Client client(argv[1], argv[2]);
	return 0;
}
