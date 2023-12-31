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
#include "../game_src/commands/command.h"

class Client {
private:
	int team;
	std::shared_ptr<InfoStruct> infoStruct;
	Queue<std::shared_ptr<Serializable>> gameStatusQueue;
	Queue<std::shared_ptr<Command>> commandsQueue;
	Sender sender;
	Receiver receiver;
	std::shared_ptr<Serializable> lastGameStatus;
	bool keepTalking = true;
	
public:
	Client(std::shared_ptr<InfoStruct> infoStruct);
	~Client();

	std::shared_ptr<Serializable> getGameStatus();
	

	void execute(std::shared_ptr<Command> command);

	void start();

	void kill();

	void join();

};
#endif
