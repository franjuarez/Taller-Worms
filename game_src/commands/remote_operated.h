#ifndef REMOTE_OPERATED_H
#define REMOTE_OPERATED_H

#include "command.h"
#include "../position.h"
#include "../../shared_src/protocol.h"
#include "../constants_game.h"


class Protocol;

class RemoteOperated : public Command {
private:
    int wormID;
    int type;
    Position pos;
    int commandType = COMMAND_REMOTE_OPERATED;
public:
    RemoteOperated(int wormsID, int type, Position pos);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    int getType();
    float getX();
    float getY();
    int getComType();
    ~RemoteOperated();
};
#endif
