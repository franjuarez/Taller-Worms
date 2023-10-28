#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
#include <iostream>


#include "sender.h"
#include "receiver.h"
#include "../shared_src/protocol.h"
#include "../game_src/game_status.h"
#include "../game_src/game_map.h"

class Client {

private:
	Protocol protocol;
	Queue<GameStatus> gameStatusQueue;
	Sender sender;
	Receiver receiver;
	
public:
	Client(const std::string&, const std::string&);
	~Client();

	std::vector<std::string> getAvailableMaps();

	// void selectMap(std::string);

	
	//game funciona como monitor y para empaquetar todo lo que se tiene que graficar

	GameStatus& getGameStatus();

	//runCommand();

	//jumpCommand();

	//shootCommand();

};
#endif
