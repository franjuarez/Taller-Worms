#ifndef TELEPORT_H
#define TELEPORT_H

#include "command.h"
#include "../position.h"
#include "../../shared_src/protocol.h"
#include "../constants_game.h"


class Protocol;

class Teleport : public Command {
private:
    int wormID;
    Position pos;
    int commandType = COMMAND_TELEPORT;
public:
    Teleport(int wormsID, Position pos);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    float getX();
    float getY();
    int getComType();
    ~Teleport();
};
#endif
