#ifndef MOVE_H
#define MOVE_H

#include "commands.h"
#include "../shared_src/protocol.h"

class Protocol;

class Move : public Command {
private:
    int wormID;
    int dir;
public:
    Move(int wormID, int dir);
    void executeCommand(GameWorld& gameWorld) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    ~Move();
};
#endif
