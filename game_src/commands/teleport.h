#ifndef TELEPORT_H
#define TELEPORT_H

#include "command.h"
#include "../position.h"
#include "../../shared_src/protocol.h"

class Protocol;

class Teleport : public Command {
private:
    int wormID;
    Position pos;
public:
    Teleport(int wormsID, Position pos);
    bool executeCommand(GameWorld& gameWorld) override;
    void send(Protocol& protocol);
    int getID();
    float getX();
    float getY();
    ~Teleport();
};
#endif
