#ifndef ATTACK_H
#define ATTACK_H

#include "command.h"
#include "../../shared_src/protocol.h"

class Protocol;

class LaunchRocket : public Command {
private:
    int type;
    int wormID;
    int dir;
    float angle;
    float power;
public:
    LaunchRocket(int type, int wormID, int dir, float angle, float power);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn) override;
    void send(Protocol& protocol);
    int getType();
    int getID();
    int getDir();
    float getAngle();
    float getPower();
    ~LaunchRocket();
};
#endif