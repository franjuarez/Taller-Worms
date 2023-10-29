#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

#include "../shared_src/protocol.h"
#include "../shared_src/queue.h"
#include "../game_src/game.h"
#include "sender.h"
#include "receiver.h"

class Player {
private:
    std::string name;
    GameLobby& gameLobby;
    Protocol protocol;
    Sender sender;
    Receiver receiver;

    Queue<Game> playerQueue;

public:
    Player(GameLobby&, Socket&&);
    ~Player();
};
#endif