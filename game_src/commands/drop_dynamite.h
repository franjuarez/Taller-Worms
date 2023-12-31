#ifndef DROP_DYNAMITE_H
#define DROP_DYNAMITE_H

#include "command.h"
#include "../../shared_src/protocol.h"

class Protocol;

class DropDynamite : public Command {
private:
    int wormID;
    int dir;
    int timer;
    int commandType = COMMAND_DYNAMITE;
public:
    DropDynamite(int wormID, int dir, int timer);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    int getTimer();
    int getDir();
    int getComType();
    ~DropDynamite();
};

#endif