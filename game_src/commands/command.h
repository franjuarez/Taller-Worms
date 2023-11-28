#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

#include "../../shared_src/protocol.h"
#include "../../physics_src/game_world.h"
#include "../../server_src/connecting_user.h"


class Protocol;
class ConnectingUser;

#define UNUSED(x) (void)(x)
class Command {

private:
    int team;
    int wormID;
public:
    Command(int wormID) : wormID(wormID) {}
    virtual ~Command() {}
    virtual bool executeCommand(GameWorld&, bool* cheatOn, bool& needsMovement) {
        std::cout << "exec mother class\n";
        *cheatOn = *cheatOn;
        needsMovement = needsMovement;
        return true;
    }
    virtual void executeCommand(ConnectingUser&) {
        std::cout << "exec mother class\n";
        return;
    }
    virtual void send(Protocol& protocol) = 0;
    virtual int getID() = 0;
};
#endif
