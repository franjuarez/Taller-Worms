#ifndef ATTACK_H
#define ATTACK_H

#include "command.h"
#include "../../shared_src/protocol.h"

class Protocol;

class LaunchRocket : public Command {
private:
    int wormID;
    int dir;
    float angle;
    float power;
public:
    LaunchRocket(int wormID, int dir, float angle, float power);
    bool executeCommand(GameWorld& gameWorld) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    float getAngle();
    float getPower();
    ~LaunchRocket();
};
#endif