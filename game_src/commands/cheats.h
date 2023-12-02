#ifndef CHEATS_H
#define CHEATS_H

#include "command.h"

class Cheats : public Command {

private:
    int wormID;
    int cheatID;
    int commandType = COMMAND_CHEAT;
public: 
    Cheats(int wormID, int cheatID);
    bool executeCommand(GameWorld& gameWorld, bool* cheatOn, bool& needsMove) override;
    void send(Protocol& protocol);
    int getID();
    int getCheatID();
    int getComType();
    ~Cheats();
};
#endif