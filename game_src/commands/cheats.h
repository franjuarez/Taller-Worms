#ifndef CHEATS_H
#define CHEATS_H

#include "command.h"

class Cheats : public Command {

private:
    int wormID;
    int cheatID;
    int health;
public: 
    Cheats(int wormID, int cheatID, int health);
    bool executeCommand(GameWorld& gameWorld) override;
    void send(Protocol& protocol);
    int getID();
    int getHealth();
    int getCheatID();
    ~Cheats();
};
#endif