#ifndef JUMP_H
#define JUMP_H

#include "commands.h"
#include "../shared_src/protocol.h"

class Protocol;

class Jump : public Command {
private:
    int wormID;
    int dir;
public:
    Jump(int wormID, int dir);
    void executeCommand(GameWorld& gameWorld) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    ~Jump();
};
#endif