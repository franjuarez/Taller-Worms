#ifndef TELEPORT_H
#define TELEPORT_H

#include "command.h"
#include "../position.h"
#include "../../shared_src/protocol.h"

class Protocol;

class Teleport : public Command {
private:
    int wormID;
    int type;
    Position pos;
public:
    Teleport(int wormsID, int type, Position pos);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    int getType();
    float getX();
    float getY();
    ~Teleport();
};
#endif
