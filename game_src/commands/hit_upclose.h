#ifndef HIT_UPCLOSE_H
#define HIT_UPCLOSE_H

#include "command.h"
#include "../position.h"
#include "../../shared_src/protocol.h"
#include "../constants_game.h"


class Protocol;

class HitUpclose : public Command {
private:
    int wormID;
    int dir;
    int commandType = COMMAND_HIT_UPCLOSE;
public:
    HitUpclose(int wormsID, int dir);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    int getComType();
    ~HitUpclose();
};
#endif
