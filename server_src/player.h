#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

#include "../shared_src/protocol.h"
#include "sender.h"
#include "receiver.h"

class Player {
private:
    std::string name;
    int id;
    Protocol protocol;
    Sender sender;
    Receiver receiver;
public:
    Player(int id, Socket&& socket);
    ~Player();
};
#endif