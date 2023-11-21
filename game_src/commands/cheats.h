#ifndef CHEATS_H
#define CHEATS_H

#include "command.h"

class Cheats : public Command {

private:
    int wormID;
    int cheatID;
public: 
    Cheats(int wormID, int cheatID);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn) override;
    void send(Protocol& protocol);
    int getID();
    int getCheatID();
    ~Cheats();
};
#endif