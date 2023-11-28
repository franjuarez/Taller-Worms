#include "../ui_src/game_view.h"
#include "client_lobby.h"
#include "../shared_src/info_struct.h"

#include <iostream>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char** argv) {
	if (argc < 3){
		throw std::runtime_error("Invalid arguments!");
		return ERROR;
	}

	try {

		// std::shared_ptr<InfoStruct> infoStruct = std::make_shared<InfoStruct>(argv[1], argv[2]);
		ClientLobby cl(argv[1], argv[2]);

		cl.run();

		// GameView gv(infoStruct);
		// gv.start();
		// gv.join();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return ERROR;
	}
	return SUCCESS;
}