#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

#include "../shared_src/protocol.h"
#include "../shared_src/queue.h"
#include "../game_src/game.h"
#include "../game_src/commands.h"
#include "sender.h"
#include "receiver.h"
#include "status_broadcaster.h"

class Player  {
private:
    GameLobby& gameLobby;
    Protocol protocol;
    StatusBroadcaster& statusBroadcaster;
    Sender sender;
    Receiver receiver;
    bool talking = true;
    
// Game queue va a ir a un monitor? no... las playerQueue van al monitos porque Queue es thread safe 
// las de Send van en monitor y la de RCV no.
    Queue<Command>& commandsQueue; // la q va al game loop tiene Commands
    Queue<Game> playerQueue; // la q viene del game loop tiene los nuevos estados

public:
    Player(GameLobby&, Socket&&, Queue<Command>&, StatusBroadcaster&);
    ~Player();
    void start();
    void join();
    void kill();
    bool isAlive();
};
#endif