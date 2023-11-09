#ifndef ATTACK_H
#define ATTACK_H

#include "commands.h"
#include "../shared_src/protocol.h"

class Protocol;

class Attack : public Command {
private:
    int wormID;
    int dir;
    float angle;
    float power;
public:
    Attack(int wormID, int dir, float angle, float power);
    void executeCommand(GameWorld& gameWorld) override;
    void send(Protocol& protocol);
    int getID();
    int getDir();
    float getAngle();
    float getPower();
    ~Attack();
};
#endif