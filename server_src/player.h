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

class InfoStruct;
class Player  {
private:
    bool talking = true;

    int playerID;

    std::shared_ptr<InfoStruct> infoStruct;

    Queue<std::shared_ptr<Command>>& commandsQueue; // la q va al game loop tiene Commands

    Queue<std::shared_ptr<Serializable>> playerQueue; // la q viene del game loop tiene los nuevos estados

    StatusBroadcaster& statusBroadcaster;

    ServerSender sender;
    ServerReceiver receiver;
public:
    Player(std::shared_ptr<InfoStruct>, int playerID, Queue<std::shared_ptr<Command>>& commandQueue, StatusBroadcaster& statusBroadcaster, std::shared_ptr<GameMap> gameMap);
    ~Player();
    void start();
    void join();
    void kill();
    bool isAlive();
};
#endif