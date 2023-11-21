#ifndef MOVE_H
#define MOVE_H

#include "command.h"
#include "../../shared_src/protocol.h"

class Protocol;

class Move : public Command {
private:
    int wormID;
    int dir;
public:
    Move(int wormID, int dir);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    ~Move();
};
#endif
