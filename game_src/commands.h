#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

#include "../shared_src/protocol.h"
#include "../physics_src/game_world.h"
class Protocol;

#define UNUSED(x) (void)(x)
class Command {

private:
    int team;
    int wormID;
public:
    Command(int team, int wormID) : team(team), wormID(wormID) {}
    virtual ~Command() {}
    virtual void executeCommand(GameWorld&) {
        std::cout << "exec mother class\n";
    }
    // podria hacer un override de exec q vaya al tipo que tiene que exec ... o no ? 
    virtual void send(Protocol& protocol) = 0;
};
#endif
