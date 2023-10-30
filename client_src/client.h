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
#include "../game_src/game_dynamic.h"
#include "../game_src/game.h"
#include "../game_src/commands.h"
class Client {

private:
	Protocol protocol;
	int team;
	Game gameStatus;	
	Queue<Game> gameStatusQueue;
	Queue<Command> commandsQueue;
	Sender sender;
	Receiver receiver;
	
public:
	Client(const std::string&, const std::string&);
	~Client();

	std::vector<std::string> getAvailableMaps();

	// void selectMap(std::string);

	
	//game funciona como monitor y para empaquetar todo lo que se tiene que graficar

	Game& getGameStatus();

	void execute(Command&);

	void run();

	//runCommand();

	//jumpCommand();

	//shootCommand();

};
#endif
