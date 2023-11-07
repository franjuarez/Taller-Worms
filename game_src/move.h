#ifndef MOVE_H
#define MOVE_H

#include "commands.h"
#include "../shared_src/protocol.h"

class Protocol;

class Move : public Command {
private:
    int wormID;
public:
    Move(int wormID);
    void executeCommand() override;
    void send(Protocol& protocol);
    int getID();
    ~Move();
};
#endif
