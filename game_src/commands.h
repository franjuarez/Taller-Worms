#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>

class Command {

private:
    int team;
    int wormID;
public:
    Command(int team, int wormID) : team(team), wormID(wormID) {}
    virtual ~Command() {}
    virtual void executeCommand() {
        std::cout << "exec mother class\n";
    };
};
#endif

