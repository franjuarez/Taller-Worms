#ifndef HIT_UPCLOSE_H
#define HIT_UPCLOSE_H

#include "command.h"
#include "../position.h"
#include "../../shared_src/protocol.h"

class Protocol;

class HitUpclose : public Command {
private:
    int wormID;
public:
    HitUpclose(int wormsID);
    bool executeCommand(GameWorld& gameWorld) override;
    void send(Protocol& protocol);
    int getID();
    ~HitUpclose();
};
#endif
