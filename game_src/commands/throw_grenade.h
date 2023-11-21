#ifndef THROW_GRENADE_H
#define THROW_GRENADE_H

#include "command.h"
#include "../../shared_src/protocol.h"

class Protocol;

class ThrowGrenade : public Command {
private:
    int type;
    int wormID;
    int dir;
    float angle;
    float power;
    int timer;
public:
    ThrowGrenade(int type, int wormID, int dir, float angle, float power, int timer);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn) override;
    void send(Protocol& protocol);
    int getType();
    int getID();
    int getDir();
    float getAngle();
    float getPower();
    int getTimer();
    ~ThrowGrenade();
};
#endif