#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>
#include <iostream>


#include "sender.h"
#include "receiver.h"
#include "../shared_src/protocol.h"
#include "../game_src/game_map.h"
#include "../game_src/game_dynamic.h"
#include "../game_src/commands.h"

class Client {
private:
	Protocol protocol;
	int team;
	Queue<Serializable*> gameStatusQueue;
	Queue<Command*> commandsQueue;
	Sender sender;
	Receiver receiver;
	Serializable* lastGameStatus;
	
public:
	Client(const std::string& hostname, const std::string& servname);
	~Client();

	std::vector<std::string> getAvailableMaps();

	// void selectMap(std::string);

	
	//game funciona como monitor y para empaquetar todo lo que se tiene que graficar

	Serializable* getGameStatus();

	void execute(Command* command);

	void start();

	void join();

	//runCommand();

	//jumpCommand();

	//shootCommand();

};
#endif
