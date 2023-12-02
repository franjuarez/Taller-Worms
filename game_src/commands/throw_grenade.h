#ifndef THROW_GRENADE_H
#define THROW_GRENADE_H

#include "command.h"
#include "../../shared_src/protocol.h"
#include "../constants_game.h"


class Protocol;

class ThrowGrenade : public Command {
private:
    int type;
    int wormID;
    int dir;
    float angle;
    float power;
    int timer;
    int commandType = COMMAND_GRENADE;
public:
    ThrowGrenade(int type, int wormID, int dir, float angle, float power, int timer);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getType();
    int getID();
    int getDir();
    float getAngle();
    float getPower();
    int getTimer();
    int getComType();
    ~ThrowGrenade();
};
#endif