#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

#include "../shared_src/protocol.h"
#include "../shared_src/queue.h"
#include "../game_src/commands/command.h"
#include "server_sender.h"
#include "server_receiver.h"
#include "status_broadcaster.h"

class Player  {
private:
    Protocol protocol;
    ServerSender sender;
    ServerReceiver receiver;
    bool talking = true;
    
// Game queue va a ir a un monitor? no... las playerQueue van al monitos porque Queue es thread safe 
// las de Send van en monitor y la de RCV no.
    Queue<std::shared_ptr<Command>>& commandsQueue; // la q va al game loop tiene Commands
    Queue<std::shared_ptr<Serializable>> playerQueue; // la q viene del game loop tiene los nuevos estados

public:
    Player(Socket&& peer, Queue<std::shared_ptr<Command>>& commandQueue, std::shared_ptr<GameMap> gameMap);
    ~Player();
    Queue<std::shared_ptr<Serializable>>* getPlayerQueue();
    void start();
    void join();
    void kill();
    bool isAlive();
};
#endif