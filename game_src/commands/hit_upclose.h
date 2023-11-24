#ifndef HIT_UPCLOSE_H
#define HIT_UPCLOSE_H

#include "command.h"
#include "../position.h"
#include "../../shared_src/protocol.h"

class Protocol;

class HitUpclose : public Command {
private:
    int wormID;
    int dir;
public:
    HitUpclose(int wormsID, int dir);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    ~HitUpclose();
};
#endif
