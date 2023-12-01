#ifndef MOVE_H
#define MOVE_H

#include "command.h"
#include "../../shared_src/protocol.h"
#include "../constants_game.h"



class Protocol;

class Move : public Command {
private:
    int wormID;
    int dir;
    int commandType = COMMAND_MOVE;
public:
    Move(int wormID, int dir);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    int getComType();
    ~Move();
};
#endif
